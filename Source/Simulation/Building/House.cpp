// Fill out your copyright notice in the Description page of Project Settings.

#include "House.h"
#include "Agent.h"
#include "RelationComponent.h"


bool AHouse::HasPlace(AAgent* agent)
{
	if (livingCost <= agent->budget)
	{
		if (visitors.Num() >= maxVisitors)
			return false;
		if (visitors.Num() > 0)
		{
			if (visitors[0] == agent)
				return true;
			URelationComponent* relationComp = visitors[0]->GetRelationComponent();
			if (relationComp->GetSignificantOther() == agent)
				return true;
			return false;
		}
		else if (requiredWorkType != EWorkType::WT_None && requiredWorkType != agent->GetWorkType())
		{
			return false;
		}
		return true;
	}
		return false;
}

bool AHouse::FixHousing(AAgent* self, AAgent* so)
{
	if (maxVisitors == 1)
		return false;
	if (so->homePlace != nullptr)
		so->homePlace->RemoveVisitor(so);
	so->homePlace = this;
	AddVisitor(so);
	return true;
}

FString AHouse::GetBuildingData_Implementation()
{
	FString dataString = "Budget needed " + FString::FromInt(livingCost) + "\n";
	dataString += "comfort gained " + FString::FromInt(gainComfort) + "\n";
	dataString += "current food amount is " + FString::FromInt(currentfood) + "\n";
	dataString += "current homeowner is" + FString::FromInt(visitors.Num()) + "\n";

	return dataString;
}
