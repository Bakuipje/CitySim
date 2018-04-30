// Fill out your copyright notice in the Description page of Project Settings.

#include "OfficePlace.h"
#include "Agent.h"






bool AOfficePlace::HasJob(AAgent* agent)
{
	bool HasExperience = agent->workExperienceMap[workType] >= neededExperience;
	return HasExperience&& visitors.Num() < maxVisitors;
}

FString AOfficePlace::GetBuildingData_Implementation()
{
	FString dataString = "Work experience needed " + FString::FromInt(neededExperience) + "\n";
	dataString += "Work experience gained " + FString::FromInt(gainExperience) + "\n";
	dataString += "Money gained " + FString::FromInt(compensation) + "\n";
	dataString += "Stress gained " + FString::FromInt(gainStress);
	return dataString;
}