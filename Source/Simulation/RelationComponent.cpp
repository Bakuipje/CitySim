// Fill out your copyright notice in the Description page of Project Settings.

#include "RelationComponent.h"
#include "Agent.h"
#include "MoodComponent.h"
#include "EngineUtils.h"
#include "Building/House.h"
#include "Building/FoodPlace.h"


// Sets default values for this component's properties
URelationComponent::URelationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	significatnOther = nullptr;

	// ...
}


// Called when the game starts
void URelationComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAgent> agentItr(GetWorld()); agentItr; ++agentItr)
	{
		AAgent* agent = *agentItr;
		if (agent != ((AAgent*)GetOwner()))
		{
			relationMap.Add(agent, FRelationStruct());
		}
	}

}


// Called every frame
void URelationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URelationComponent::isFriendly(AAgent* agent)
{
	return relationMap[agent].relationShip > friendlyValue;
}

bool URelationComponent::isHostile(AAgent* agent)
{
	return relationMap[agent].relationShip < hostileValue;
}

bool URelationComponent::isReligious()
{
	return religious;
}

bool URelationComponent::isAthletic()
{
	return athletic;
}

void URelationComponent::CheckFoodmap()
{
	bool empty = true;
	for (auto& elem : foodMap)
	{
		if (elem.Value > 0)
			empty = false;
	}
	if (empty)
		FillFoodMap();
}

void URelationComponent::FillFoodMap()
{
	int fastVal, normalVal, fancyVal;
	GetFoodValue(fastVal, normalVal, fancyVal);
	if (foodMap.Num() == 0)
	{
		foodMap.Add((int)EFoodType::EF_FastFood, fastVal);
		foodMap.Add((int)EFoodType::EF_NormalFood, normalVal);
		foodMap.Add((int)EFoodType::EF_FancyFood, fancyVal);
	}
	else
	{
		foodMap[(int)EFoodType::EF_FastFood] = fastVal;
		foodMap[(int)EFoodType::EF_NormalFood] = normalVal;
		foodMap[(int)EFoodType::EF_FancyFood] = fancyVal;
	}
}

void URelationComponent::GetFoodValue(int &fastValue, int & normalValue, int &fancyValue)
{
	AAgent* owner = (AAgent*)GetOwner();
	EHouseType houserType;
	if (owner->homePlace == nullptr)
		houserType = EHouseType::EH_HomelessHouse;
	else houserType = owner->homePlace->houseType;
	switch (houserType)
	{
	case EHouseType::EH_HomelessHouse:
		fastValue = 3;
		normalValue = 0;
		fancyValue = 0;
		break;
	case EHouseType::EH_NormalHouse:
		fastValue = 2;
		normalValue = 3;
		fancyValue = 1;
		break;
	case EHouseType::EH_FancyHouse:
		fastValue = 1;
		normalValue = 3;
		fancyValue = 3;
		break;
	default:
		break;
	}
}

void URelationComponent::AddRelationStats(AAgent* otherAgent, float value)
{
	relationMap[otherAgent].relationShip += value;
	if (relationMap[otherAgent].relationShip > friendlyValue)
		AddSignificatnOther(otherAgent);
}

void URelationComponent::AddSignificatnOther(AAgent* otherAgent)
{
	URelationComponent* otherrel = (URelationComponent*)otherAgent->GetComponentByClass(URelationComponent::StaticClass());
	if (otherrel->GetSignificantOther() == nullptr && GetSignificantOther() == nullptr)
	{
		significatnOther = otherAgent;
		otherrel->significatnOther = (AAgent*)GetOwner();
		otherAgent->GetMoodComponent()->AddThinkingString(FString("fell in love with " + GetOwner()->GetFName().ToString()));
		((AAgent*)GetOwner())->GetMoodComponent()->AddThinkingString(FString("fell in love with " + otherAgent->GetFName().ToString()));;
		if (((AAgent*)GetOwner())->homePlace != nullptr && !((AAgent*)GetOwner())->homePlace->FixHousing(((AAgent*)GetOwner()), otherAgent))
		{
			if (otherAgent->homePlace != nullptr)
				otherAgent->homePlace->FixHousing(otherAgent, ((AAgent*)GetOwner()));
		}
	}
}

float URelationComponent::GetFriendlyValue(AAgent* otherAgent)
{
	if(relationMap.Contains(otherAgent))
		return relationMap[otherAgent].relationShip;
	else return 0;
}


AAgent* URelationComponent::GetSignificantOther()
{
	return significatnOther;
}
