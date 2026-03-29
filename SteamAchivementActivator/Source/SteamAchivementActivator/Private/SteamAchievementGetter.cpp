// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamAchievementGetter.h"
#include "SteamAchievementQueryAsync.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AchievementData.h"
#include "steam/isteamuserstats.h"

void USteamAchievementGetter::Activate()
{
    Super::Activate();
    AddToRoot();
    queryAsync = USteamAchievementQueryAsync::QueryAchievements(playerController);
    queryAsync->OnAchivementQueryedSuccess().AddDynamic(this, &USteamAchievementGetter::GetAchievementInternal);
    queryAsync->OnAchivementQueryedFailed().AddDynamic(this, &USteamAchievementGetter::OnFailedAction);
    queryAsync->Activate();
}

USteamAchievementGetter* USteamAchievementGetter::GetAchivement(APlayerController* _playerController, UAchievementData* _achievementData)
{
    return GetAchivementById(_playerController, _achievementData->steamAPIName);
}

USteamAchievementGetter* USteamAchievementGetter::GetAchivementById(APlayerController* _playerController, FString _steamApiName)
{
    TObjectPtr< USteamAchievementGetter> _this = NewObject<USteamAchievementGetter>();
    _this->playerController = _playerController;
    _this->steamAchievementId = _steamApiName;
    return _this;
}

void USteamAchievementGetter::GetAchievementInternal()
{
    IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get();
    if (!_subsystem) return;



    IOnlineAchievementsPtr _achievements = _subsystem->GetAchievementsInterface();
    if (!_achievements.IsValid()) return;
    FUniqueNetIdPtr _userId = playerController->PlayerState->GetUniqueId().GetUniqueNetId();
    FOnlineAchievement _achievement;
    EOnlineCachedResult::Type _result =  _achievements->GetCachedAchievement(
        *_userId,
        steamAchievementId,
        _achievement
    );

    if (_result == EOnlineCachedResult::Type::NotFound)
        onAchivementGetDataFailed.Broadcast();
    else
        onAchivementGetDataSuccess.Broadcast();
}

void USteamAchievementGetter::OnFailedAction()
{
    onAchivementGetDataFailed.Broadcast();
    RemoveFromRoot();
    SetReadyToDestroy();
}
