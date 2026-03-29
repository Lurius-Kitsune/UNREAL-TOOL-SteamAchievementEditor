// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamAchievementUnlocker.h"
#include "SteamAchievementQueryAsync.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AchievementData.h"

void USteamAchievementUnlocker::Activate()
{
	Super::Activate();
	AddToRoot();
	queryAsync = USteamAchievementQueryAsync::QueryAchievements(playerController);
	queryAsync->OnAchivementQueryedSuccess().AddDynamic(this, &USteamAchievementUnlocker::UpdateAchievementInternal);
	queryAsync->OnAchivementQueryedFailed().AddDynamic(this, &USteamAchievementUnlocker::OnFailedAction);
    queryAsync->Activate();
}

USteamAchievementUnlocker* USteamAchievementUnlocker::UpdateAchivement(APlayerController* _playerController, UAchievementData* _achievementData, float _progress)
{
	TObjectPtr< USteamAchievementUnlocker> _this = NewObject<USteamAchievementUnlocker>();
	_this->playerController = _playerController;
	_this->steamAchievementId = _achievementData->steamAPIName;
	_this->progression = _progress;
	return _this;
}

USteamAchievementUnlocker* USteamAchievementUnlocker::UpdateAchivementById(APlayerController* _playerController, FString _steamAchievementId, float _progress)
{
    TObjectPtr< USteamAchievementUnlocker> _this = NewObject<USteamAchievementUnlocker>();
    _this->playerController = _playerController;
    _this->steamAchievementId = _steamAchievementId;
    _this->progression = _progress;
    return _this;
}

USteamAchievementUnlocker* USteamAchievementUnlocker::UnlockAchievement(APlayerController* _playerController, UAchievementData* _achievementData, bool _unlockState)
{
    return UpdateAchivement(_playerController, _achievementData, _unlockState ? 1.f : -1.f);
}

USteamAchievementUnlocker* USteamAchievementUnlocker::UnlockAchievementById(APlayerController* _playerController, FString _steamAchievementId, bool _unlockState)
{
    return UpdateAchivementById(_playerController, _steamAchievementId, _unlockState ? 1.f : -1.f);
}

void USteamAchievementUnlocker::UpdateAchievementInternal()
{
    IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get();
    if (!_subsystem) return;

    IOnlineAchievementsPtr _achievements = _subsystem->GetAchievementsInterface();
    if (!_achievements.IsValid()) return;

    FOnlineAchievementsWritePtr _writeObject = MakeShareable(new FOnlineAchievementsWrite());
    _writeObject->SetFloatStat(steamAchievementId, 100.0f);


    FUniqueNetIdPtr _userId = playerController->PlayerState->GetUniqueId().GetUniqueNetId();

    FOnlineAchievementsWriteRef _achievementsWriteObjectRef = _writeObject.ToSharedRef();

    _achievements->WriteAchievements(
        *_userId,
        _achievementsWriteObjectRef,
        FOnAchievementsWrittenDelegate::CreateLambda(
            [&](const FUniqueNetId& _playerId, bool _bSuccess)
            {
                UE_LOG(LogTemp, Log, TEXT("Achievement unlocked: %d"), _bSuccess);
                if(_bSuccess)
					onAchivementUpdatedSuccess.Broadcast();
				else
					onAchivementUpdatedFailed.Broadcast();

                RemoveFromRoot();
                SetReadyToDestroy();
            })
    );
}

void USteamAchievementUnlocker::OnFailedAction()
{
	onAchivementUpdatedFailed.Broadcast();
    RemoveFromRoot();
    SetReadyToDestroy();
}
