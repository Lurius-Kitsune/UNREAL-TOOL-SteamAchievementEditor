// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <steam/isteamuserstats.h>

#include "AchievementSubsystemV2.h"
#include "CoreMinimal.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SteamStatsUtility.generated.h"

class UAchievementData;
/**
 * 
 */
UCLASS()
class STEAMACHIVEMENTACTIVATOR_API USteamStatsUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
private:
	//UFUNCTION(BlueprintPure, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	FORCEINLINE static bool IsStatsReady(const UObject* _worldContext)
	{
		UGameInstance* _gameInstance = UGameplayStatics::GetGameInstance(_worldContext);
		if (!_gameInstance) return false;

		UAchievementSubsystemV2* _sub = _gameInstance->GetSubsystem<UAchievementSubsystemV2>();
		if (!_sub) return false;
		return _sub->IsStatsReady();
	}
	
public:
	UFUNCTION(BlueprintPure, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool GetUserStat(const UObject* _worldContext, const UAchievementData* _achievementData, float& _outValue);
	UFUNCTION(BlueprintPure, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool GetUserStatById(const UObject* _worldContext,const FString& _steamApi, float& _outValue);

	
#pragma region === FLOAT ===

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserFloatStatsAdditive(const UObject* _worldContext,const UAchievementData* _achievementData, float _additive);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserFloatStatsAdditiveById(const UObject* _worldContext,const FString& _steamApi, float _additive);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserFloatStats(const UObject* _worldContext,const UAchievementData* _achievementData, float _progress);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserFloatStatsById(const UObject* _worldContext,const FString& _steamApi, float _progress);
#pragma endregion
	
#pragma region === INT ===
	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserIntStatsAdditive(const UObject* _worldContext,const UAchievementData* _achievementData, int32 _additive);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserIntStatsAdditiveById(const UObject* _worldContext,const FString& _steamApi, int32 _additive);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserIntStats(const UObject* _worldContext,const UAchievementData* _achievementData, int32 _progress);

	UFUNCTION(BlueprintCallable, Category = "Steam|Stats", meta = (WorldContext = "_worldContext"))
	static bool EditUserIntStatsById(const UObject* _worldContext,const FString& _steamApi, int32 _progress);
#pragma endregion

};
