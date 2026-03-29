// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamStatsUtility.h"
#include "AchievementData.h"
#include "steam/isteamuserstats.h"


bool USteamStatsUtility::GetUserStat(const UObject* _worldContext, const UAchievementData* _achievementData, float& _outValue)
{
	return GetUserStatById(_worldContext,_achievementData->statsNameId, _outValue);
}

bool USteamStatsUtility::GetUserStatById(const UObject* _worldContext, const FString& _steamApi, float& _outValue)
{
	if (!IsStatsReady(_worldContext))
	{
		UKismetSystemLibrary::PrintString(_worldContext, TEXT("[SteamStatsUtils] NOT READY"), true, true, FLinearColor::Red, 5.f);
		return false;
	}

	ISteamUserStats* _userStats = SteamUserStats();
	if (!_userStats)
		return false;

	const char* _statName = TCHAR_TO_ANSI(*_steamApi);
	int32 _intValue = 0;
	if (_userStats->GetStat(_statName, &_outValue))
	{
		UKismetSystemLibrary::PrintString(_worldContext, FString::Printf(TEXT("[SteamStatsUtils] [float] %s = %f"), *_steamApi, _outValue), true, true, FLinearColor::Green, 5.f);
		return true;
	} else if (_userStats->GetStat(_statName, &_intValue))
	{
		_outValue = _intValue;
		UKismetSystemLibrary::PrintString(_worldContext, FString::Printf(TEXT("[SteamStatsUtils] [Int] %s = %i"), *_steamApi, _intValue), true, true, FLinearColor::Green, 5.f);
		return true;
	}
	UKismetSystemLibrary::PrintString(_worldContext, FString::Printf(TEXT("[SteamStatsUtils] Stat not found: %s"), *_steamApi), true, true, FLinearColor::Red, 5.f);
	return false;
}

#pragma region === FLOAT ===
bool USteamStatsUtility::EditUserFloatStatsAdditive(const UObject* _worldContext, const UAchievementData* _achievementData, float _additive)
{
	return EditUserFloatStatsAdditiveById(_worldContext,_achievementData->statsNameId, _additive);
}

bool USteamStatsUtility::EditUserFloatStatsAdditiveById(const UObject* _worldContext, const FString& _steamApi, float _additive)
{
	if (!IsStatsReady(_worldContext))
		return false;
	float _outValue = 0.0f;
	if(GetUserStatById(_worldContext, _steamApi, _outValue))
		return EditUserFloatStatsById(_worldContext, _steamApi, _outValue + _additive);
	return false;
}

bool USteamStatsUtility::EditUserFloatStats(const UObject* _worldContext, const UAchievementData* _achievementData, float _progress)
{
	return EditUserFloatStatsById(_worldContext, _achievementData->statsNameId, _progress);
}

bool USteamStatsUtility::EditUserFloatStatsById(const UObject* _worldContext, const FString& _steamApi, float _progress)
{
	if (!IsStatsReady(_worldContext))
		return false;
	ISteamUserStats* _userStats = SteamUserStats();
	if (!_userStats)
		return false;

	return _userStats->SetStat(TCHAR_TO_ANSI(*_steamApi), _progress);
}

#pragma endregion

#pragma region === INT ===

bool USteamStatsUtility::EditUserIntStatsAdditive(const UObject* _worldContext,
	const UAchievementData* _achievementData, int32 _additive)
{
	return EditUserIntStatsAdditiveById(_worldContext, _achievementData->statsNameId, _additive);
}

bool USteamStatsUtility::EditUserIntStatsAdditiveById(const UObject* _worldContext, const FString& _steamApi,
	int32 _additive)
{
	if (!IsStatsReady(_worldContext))
		return false;
	float _outValue = 0.0f;
	if(GetUserStatById(_worldContext, _steamApi, _outValue))
		return EditUserIntStatsById(_worldContext, _steamApi, _outValue + _additive);
	return false;
}

bool USteamStatsUtility::EditUserIntStats(const UObject* _worldContext, const UAchievementData* _achievementData,
	int32 _progress)
{
	return EditUserIntStatsById(_worldContext, _achievementData->statsNameId, _progress);
}

bool USteamStatsUtility::EditUserIntStatsById(const UObject* _worldContext, const FString& _steamApi, int32 _progress)
{
	if (!IsStatsReady(_worldContext))
		return false;
	ISteamUserStats* _userStats = SteamUserStats();
	if (!_userStats)
		return false;

	return _userStats->SetStat(TCHAR_TO_ANSI(*_steamApi), _progress);
}
#pragma endregion