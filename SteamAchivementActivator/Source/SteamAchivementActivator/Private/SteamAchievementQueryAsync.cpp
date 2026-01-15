// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamAchievementQueryAsync.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AchievementData.h"

void USteamAchievementQueryAsync::Activate()
{
	Super::Activate();
	QueryAchievementsInternal();
}

USteamAchievementQueryAsync* USteamAchievementQueryAsync::QueryAchievements(APlayerController* _playerController)
{
	TObjectPtr<USteamAchievementQueryAsync> _this = NewObject<USteamAchievementQueryAsync>();
	_this->playerController = _playerController;
	return _this;
}

void USteamAchievementQueryAsync::QueryAchievementsInternal()
{
    UKismetSystemLibrary::PrintString(
        this,
        FString::Printf(
            TEXT("Querying Achievements.. test")
        )
    );
    IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get();
    if (!_subsystem) return;

    IOnlineAchievementsPtr _achievements = _subsystem->GetAchievementsInterface();
    if (!_achievements.IsValid()) return;

    FUniqueNetIdPtr UserId = playerController->PlayerState->GetUniqueId().GetUniqueNetId();

    _achievements->QueryAchievements(
        *UserId,
        FOnQueryAchievementsCompleteDelegate::CreateLambda(
            [&](const FUniqueNetId& _playerId, bool _bSuccess)
            {
                UE_LOG(LogTemp, Log, TEXT("Achievements loaded: %d"), _bSuccess);
                UKismetSystemLibrary::PrintString(
                    this,
                    FString::Printf(
                        TEXT("Querying Achievements.. %s"),
                        _bSuccess ? TEXT("SUCCESS") : TEXT("FAILED")
                    )
                );

                if(_bSuccess)
					onAchivementQueryedSuccess.Broadcast();
                else
					onAchivementQueryedFailed.Broadcast();

            })
    );
}
