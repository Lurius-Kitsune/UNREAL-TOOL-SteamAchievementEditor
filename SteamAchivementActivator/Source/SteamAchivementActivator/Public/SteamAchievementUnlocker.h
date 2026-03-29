// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SteamAchievementUnlocker.generated.h"

/**
 * 
 */

class UAchievementData;
class USteamAchievementQueryAsync;

UCLASS()
class STEAMACHIVEMENTACTIVATOR_API USteamAchievementUnlocker : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementUpdatedSuccess);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementUpdatedFailed);
	UPROPERTY(BlueprintAssignable)
	FOnAchivementUpdatedSuccess onAchivementUpdatedSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnAchivementUpdatedFailed onAchivementUpdatedFailed;

	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;

	UPROPERTY()
	FString steamAchievementId = FString();

	UPROPERTY()
	float progression = 0.f;

	UPROPERTY()
	TObjectPtr<USteamAchievementQueryAsync> queryAsync = nullptr;
public:
	FORCEINLINE FOnAchivementUpdatedSuccess& OnAchivementUpdatedSuccess() { return onAchivementUpdatedSuccess;  }
	FORCEINLINE FOnAchivementUpdatedFailed& OnAchivementUpdatedFailed() { return onAchivementUpdatedFailed;  }
public:
	virtual void Activate() override;

	/// <summary>
	/// Update the achievement with a progressive state.
	/// Can be use by boolean Achievement but please use See <see cref="UnlockAchievement"/>. 
	/// </summary>
	/// <param name="_playerController">Player controller</param>
	/// <param name="_achievementData">The achievement</param>
	/// <param name="_progress">1 to activate, 0 do nothing, -1 disable it</param>
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementUnlocker* UpdateAchivement(APlayerController* _playerController, UAchievementData* _achievementData, float _progress = 1.f);
	
	/// <summary>
	/// Update the achievement with a progressive state.
	/// Can be use by boolean Achievement but please use See <see cref="UnlockAchievement"/>. 
	/// </summary>
	/// <param name="_playerController">Player controller</param>
	/// <param name="_achievementData">The achievement</param>
	/// <param name="_progress">1 to activate, 0 do nothing, -1 disable it</param>
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementUnlocker* UpdateAchivementById(APlayerController* _playerController, FString _steamAchievementId, float _progress = 1.f);

	/// <summary>
	/// Unlock totaly an achievement
	/// </summary>
	/// <param name="_playerController"></param>
	/// <param name="_achievementData"></param>
	/// <param name="_unlockState"></param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementUnlocker* UnlockAchievement(APlayerController* _playerController, UAchievementData* _achievementData, bool _unlockState = true);

	/// <summary>
	/// Unlock totaly an achievement
	/// </summary>
	/// <param name="_playerController"></param>
	/// <param name="_achievementData"></param>
	/// <param name="_unlockState"></param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementUnlocker* UnlockAchievementById(APlayerController* _playerController, FString _steamAchievementId, bool _unlockState = true);


private:
	UFUNCTION()
	void UpdateAchievementInternal();
	UFUNCTION()
	void OnFailedAction();
};
