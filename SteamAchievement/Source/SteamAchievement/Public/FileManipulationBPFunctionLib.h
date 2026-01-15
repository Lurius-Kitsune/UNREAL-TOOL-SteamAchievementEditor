// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileManipulationBPFunctionLib.generated.h"

class UAchievementData;

/**
 * 
 */
UCLASS()
class STEAMACHIEVEMENT_API UFileManipulationBPFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintCallable, Category = "File")
	static TArray<FString> ReadAllFile(const FString& _filePath)
	{
		TArray<FString> fileContent;
		FFileHelper::LoadFileToStringArray(fileContent, *_filePath);
		return fileContent;
	}

	UFUNCTION(BlueprintCallable, Category = "Achievements Tools")
	static UAchievementData* CreateAchievementDataAsset(FString AssetName, FString SteamID, FString FolderPath);

	UFUNCTION(BlueprintCallable, Category = "File")
	static bool WriteAllOnFile(const FString& _filePath, const TArray<FString>& _data)
	{
		//FFileHelper(*_filePath, false);
		return FFileHelper::SaveStringArrayToFile(_data, *_filePath);
	}
};
