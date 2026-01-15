//// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SteamAchievementQueryAsync.generated.h"


class UAchievementData;

UCLASS()
class STEAMACHIVEMENTACTIVATOR_API USteamAchievementQueryAsync : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementQueryedSuccess);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchivementQueryedFailed);

	UPROPERTY(BlueprintAssignable)
	FOnAchivementQueryedSuccess onAchivementQueryedSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnAchivementQueryedFailed onAchivementQueryedFailed;

	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;

public:
	FORCEINLINE FOnAchivementQueryedSuccess& OnAchivementQueryedSuccess() { return onAchivementQueryedSuccess; }
	FORCEINLINE FOnAchivementQueryedFailed& OnAchivementQueryedFailed() { return onAchivementQueryedFailed; }

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "Achievements", meta = (BlueprintInternalUseOnly = true))
	static USteamAchievementQueryAsync* QueryAchievements(APlayerController* _playerController);
private:
	void QueryAchievementsInternal();
};
