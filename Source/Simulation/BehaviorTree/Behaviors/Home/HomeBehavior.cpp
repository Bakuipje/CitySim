// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeBehavior.h"
#include "MoodComponent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include "Building/House.h"
#include "EngineUtils.h"



void UHomeBehavior::BeginPlay()
{
	homeTimer = homeDuration;
}

void UHomeBehavior::Reset()
{
	URGBehaviorTreeBase::Reset();
	homeTimer = homeDuration;
}
EBehaviorState UHomeBehavior::Tick_Implementation(float deltaTime)
{
	if (homeTimer <= 0)
	{
		FindBetterHome();
		AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
		owner->stamina = 10 * owner->exersice;
		if (IsValid(owner->homePlace))
			owner->homePlace->AddRelationShips(owner, 0.3f, 0.1f);

		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	homeTimer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}

void UHomeBehavior::FindBetterHome()
{
	float closestdist = 1e34;
	AHouse* bestHousePlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();

	if (world == nullptr || !IsValid(ownerActor->homePlace))
	{
		return;
	}
	int highestCompensation = ownerActor->homePlace->livingCost;

	for (TActorIterator<AHouse> officeItr(world); officeItr; ++officeItr)
	{
		AHouse* homePlace = *officeItr;
		if (!homePlace->HasPlace(ownerActor))
			continue;
		float dist = FVector::DistSquared2D(homePlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());
		if (homePlace->livingCost > highestCompensation)//dist < closestdist)
		{
			highestCompensation = homePlace->livingCost;
			bestHousePlace = homePlace;
			closestdist = dist;
		}
	}

	if (bestHousePlace == nullptr)
	{
		AddPrintString(FString("failed to find a better Home"));
		return;
	}
	AddPrintString("found better Home" + FString::FromInt(highestCompensation));
	ownerActor->homePlace->RemoveVisitor(ownerActor);
	ownerActor->homePlace = bestHousePlace;
	bestHousePlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestHousePlace, 0);// = bestHousePlace;

}