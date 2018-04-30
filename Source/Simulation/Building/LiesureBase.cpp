// Fill out your copyright notice in the Description page of Project Settings.

#include "LiesureBase.h"
#include "Agent.h"
#include "RelationComponent.h"



bool ALiesureBase::HasPlace(AAgent* agent)
{
	bool hasPlace = visitors.Num() < maxVisitors&& agent->budget>cost && IsOpenAtArrival(agent);
	if(!religiousPlace)
		return hasPlace;
	else return agent->GetRelationComponent()->isReligious() && hasPlace;

}

FString ALiesureBase::GetBuildingData_Implementation()
{
	FString dataString = "Budget needed " + FString::FromInt(cost) + "\n";
	dataString += "comfort gained " + FString::FromInt(liesureAmount) + "\n";

	return dataString;
}
