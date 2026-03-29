#pragma once

#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AchievementSubsystemV2.generated.h"

class USteamAchievementUnlocker;
class UAchievementData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsReady);

UCLASS()
class STEAMACHIVEMENTACTIVATOR_API UAchievementSubsystemV2 : public UGameInstanceSubsystem
{
    GENERATED_BODY()

private:
    UPROPERTY()
    TObjectPtr<USteamAchievementUnlocker> currentNode;


    FTimerHandle retryTimerHandle;
    bool statsReady = false;
    bool isSteam = false;
    int32 retryCount = 0;

    static constexpr int32 MAX_RETRIES = 5;
    static constexpr float RETRY_DELAY = 2.f;

public:
    UPROPERTY(BlueprintAssignable, Category = "Steam|Stats")
    FOnStatsReady onStatsReady;
    
    UFUNCTION(BlueprintPure, Category = "Steam|Stats")
    FORCEINLINE bool IsStatsReady() const { return statsReady; }
protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
    UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
    void UnlockAchievement(APlayerController* _playerController, UAchievementData* _achievementData);

    UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
    void UnlockAchievementById(APlayerController* _playerController, const FString& _achievementId);

    void QueryStats();

private:
    void QueryStats_Steam();
    STEAM_CALLBACK(UAchievementSubsystemV2, OnUserStatsReceived, UserStatsReceived_t);

    UFUNCTION()
    void OnSuccess();

    UFUNCTION()
    void OnFailed();
};