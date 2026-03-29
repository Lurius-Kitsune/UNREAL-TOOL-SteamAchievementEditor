#include "AchievementSubsystemV2.h"
#include "SteamAchievementUnlocker.h"

#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "OnlineError.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "steam/steam_api.h"

void UAchievementSubsystemV2::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    GetWorld()->GetTimerManager().SetTimer(
        retryTimerHandle,
        this,
        &UAchievementSubsystemV2::QueryStats,
        5.f,
        false
    );
    
    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[AchievementSubsystem] Initialized"), true, true, FLinearColor::Green, 5.f);
}

// =====================
//   QUERY STATS
// =====================

void UAchievementSubsystemV2::QueryStats()
{
    IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get();
    if (!_subsystem)
    {
        UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[AchievementSubsystem] No OnlineSubsystem found"), true, true, FLinearColor::Red, 5.f);
        return;
    }
    FName _subsystemName = _subsystem->GetSubsystemName();
    UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("[AchievementSubsystem] Subsystem: %s"), *_subsystemName.ToString()), true, true, FLinearColor::Green, 5.f);

    if (_subsystemName == "Steam")
    {
        QueryStats_Steam();
        isSteam = true;
    }
    else
        UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("[AchievementSubsystem] Subsystem '%s' not supported"), *_subsystemName.ToString()), true, true, FLinearColor::Red, 5.f);
}

void UAchievementSubsystemV2::QueryStats_Steam()
{
#if !UE_SERVER
    if (!SteamUserStats())
    {
        if (retryCount < MAX_RETRIES)
        {
            retryCount++;
            UKismetSystemLibrary::PrintString(GetWorld(),
                FString::Printf(TEXT("[AchievementSubsystem] SteamUserStats null, retry %d/%d"), retryCount, MAX_RETRIES),
                true, true, FLinearColor::Yellow, 5.f);

            GetWorld()->GetTimerManager().SetTimer(retryTimerHandle, this, &UAchievementSubsystemV2::QueryStats_Steam, RETRY_DELAY, false);
        }
        else
        {
            UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[AchievementSubsystem] SteamUserStats failed after max retries"), true, true, FLinearColor::Red, 5.f);
        }
        return;
    }

    retryCount = 0;

    bool _requested = SteamUserStats()->RequestCurrentStats();
    UKismetSystemLibrary::PrintString(GetWorld(),
        FString::Printf(TEXT("[AchievementSubsystem] RequestCurrentStats: %s"), _requested ? TEXT("OK") : TEXT("FAILED")),
        true, true, FLinearColor::Green, 5.f);

#endif
}

void UAchievementSubsystemV2::OnUserStatsReceived(UserStatsReceived_t* _param)
{
#if !UE_SERVER
    statsReady = _param->m_eResult == EResult::k_EResultOK;
    onStatsReady.Broadcast();
    FLinearColor _color = statsReady ? FLinearColor::Green : FLinearColor::Red;
    UKismetSystemLibrary::PrintString(GetWorld(), 
        FString::Printf(TEXT("[AchievementSubsystem] Stats %s !"),
            statsReady ? TEXT("RECEIVED") : TEXT("FAILED")),
        true, 
        true, 
        _color, 
        8.f);
#endif
}

// =====================
//   ACHIEVEMENTS
// =====================

void UAchievementSubsystemV2::UnlockAchievement(APlayerController* _playerController, UAchievementData* _achievementData)
{
    if (!_playerController || !_achievementData) return;

    currentNode = USteamAchievementUnlocker::UnlockAchievement(_playerController, _achievementData, true);
    if (!currentNode) return;

    currentNode->OnAchivementUpdatedSuccess().AddDynamic(this, &UAchievementSubsystemV2::OnSuccess);
    currentNode->OnAchivementUpdatedFailed().AddDynamic(this, &UAchievementSubsystemV2::OnFailed);
    currentNode->Activate();
}

void UAchievementSubsystemV2::UnlockAchievementById(APlayerController* _playerController, const FString& _achievementId)
{
    if (!_playerController || _achievementId.IsEmpty()) return;

    currentNode = USteamAchievementUnlocker::UnlockAchievementById(_playerController, _achievementId, true);
    if (!currentNode) return;

    currentNode->OnAchivementUpdatedSuccess().AddDynamic(this, &UAchievementSubsystemV2::OnSuccess);
    currentNode->OnAchivementUpdatedFailed().AddDynamic(this, &UAchievementSubsystemV2::OnFailed);
    currentNode->Activate();
}

// =====================
//   CALLBACKS
// =====================

void UAchievementSubsystemV2::OnSuccess()
{
    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[AchievementSubsystem] Achievement unlocked successfully"), true, true, FLinearColor::Green, 5.f);
}

void UAchievementSubsystemV2::OnFailed()
{
    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("[AchievementSubsystem] Achievement unlock failed"), true, true, FLinearColor::Red, 5.f);
}