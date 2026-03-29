// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteamAchievementUnlocker.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "SteamAchievementGetter.generated.h"

//struct FOnlineAchievement;

/**
 * 
 */
UCLASS()
class STEAMACHIVEMENTACTIVATOR_API USteamAchievementGetter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementGetDataSuccess);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementGetDataFailed);

	UPROPERTY(BlueprintAssignable)
	FOnAchivementGetDataSuccess onAchivementGetDataSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnAchivementGetDataFailed onAchivementGetDataFailed;

	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;

	UPROPERTY()
	FString steamAchievementId = FString();

	UPROPERTY()
	TObjectPtr<USteamAchievementQueryAsync> queryAsync = nullptr;

public:
	virtual void Activate() override;

	/// <summary>
	/// Update the achievement with a progressive state.
	/// Can be use by boolean Achievement but please use See <see cref="UnlockAchievement"/>. 
	/// </summary>
	/// <param name="_playerController">Player controller</param>
	/// <param name="_achievementData">The achievement</param>
	/// <param name="_progress">1 to activate, 0 do nothing, -1 disable it</param>
	UFUNCTION(BlueprintCallable, Category = "Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementGetter* GetAchivement(APlayerController* _playerController, UAchievementData* _achievementData);

	UFUNCTION(BlueprintCallable, Category = "Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementGetter* GetAchivementById(APlayerController* _playerController, FString _steamApiName);

private:
	UFUNCTION()
	void GetAchievementInternal();
	UFUNCTION()
	void OnFailedAction();
};
