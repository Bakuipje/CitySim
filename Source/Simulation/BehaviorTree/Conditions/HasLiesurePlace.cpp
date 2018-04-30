// Fill out your copyright notice in the Description page of Project Settings.

#include "HasLiesurePlace.h"
#include "Agent.h"
#include "Building/LiesureBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

bool UHasLiesurePlace::Execute_Implementation()
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if (agent->liesurePlace != nullptr)
		agent->moveLocation.Insert(agent->liesurePlace,0);
	return agent->liesurePlace != nullptr;
}
