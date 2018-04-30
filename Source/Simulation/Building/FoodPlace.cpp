// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodPlace.h"
#include "Agent.h"
#include "House.h"
#include "RelationComponent.h"

bool AFoodPlace::HasPlace(AAgent* agent)
{
	agent->GetRelationComponent()->CheckFoodmap();
	if (agent->GetRelationComponent()->foodMap[(int)foodType] <= 0)
		return false;
 	bool notHomeless = agent->homePlace != nullptr && agent->homePlace->houseType != EHouseType::EH_HomelessHouse;
	if (!allowHomeless && !notHomeless)
		return false;
	if (agent->budget > cost)
		return true;
	return false;
}

FString AFoodPlace::GetBuildingData_Implementation()
{
	FString dataString = "Budget needed " + FString::FromInt(cost) + "\n";
	dataString += "food gained " + FString::FromInt(foodAmount) + "\n";
	return dataString;
}


