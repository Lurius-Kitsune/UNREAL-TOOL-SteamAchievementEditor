// Fill out your copyright notice in the Description page of Project Settings.


#include "FileManipulationBPFunctionLib.h"
#include "Factories/DataAssetFactory.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AchievementData.h"
#include "EditorAssetLibrary.h"

UAchievementData* UFileManipulationBPFunctionLib::CreateAchievementDataAsset(FString AssetName, FString SteamID, FString FolderPath)
{
    // Sécurité : chemin valide
    if (!FolderPath.StartsWith(TEXT("/Game")))
    {
        FolderPath = TEXT("/Game/") + FolderPath;
    }

    // Créer le dossier s’il n’existe pas
    if (!UEditorAssetLibrary::DoesDirectoryExist(FolderPath))
    {
        UEditorAssetLibrary::MakeDirectory(FolderPath);
    }


    FAssetToolsModule& _assetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
    IAssetTools& _assetTools = _assetToolsModule.Get();

    UDataAssetFactory* _factory = NewObject<UDataAssetFactory>();
    _factory->DataAssetClass = UAchievementData::StaticClass();

    UObject* _newAssetObject = _assetTools.CreateAsset(
        AssetName,
        FolderPath,
        UAchievementData::StaticClass(),
        _factory
    );

    UAchievementData* _achievement = Cast<UAchievementData>(_newAssetObject);
    if (!_achievement)
        return nullptr;

    _achievement->steamAPIName = SteamID;
    _achievement->displayName = FText::FromString(AssetName);

    _achievement->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(_achievement);

    return _achievement;
}