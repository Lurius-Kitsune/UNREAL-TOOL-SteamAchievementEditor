// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AchievementData.generated.h"

UENUM(BlueprintType)
enum class EAchivementType : uint8
{
	AT_BoolAchivement UMETA(DisplayName = "Boolean Achievement"),
	AT_ProgressiveAchivement UMETA(DisplayName = "Progressive Achievement")
};

UCLASS(BlueprintType)
class STEAMACHIVEMENTACTIVATOR_API UAchievementData : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    FString steamAPIName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    FText displayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	FString statsNameId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	float maxValueStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	EAchivementType achivementType = EAchivementType::AT_BoolAchivement;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	bool isBinded = false;
};
