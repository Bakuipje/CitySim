// Fill out your copyright notice in the Description page of Project Settings.

#include "HasJob.h"
#include "Agent.h"
#include "Building/OfficePlace.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

bool UHasJob::Execute_Implementation()
{
	AAgent* agent = Cast<AAgent>(m_ownerComp->GetOwner());
	if(agent->workPlace!= nullptr)
		agent->moveLocation.Insert( agent->workPlace,0);
	return IsValid(agent->workPlace);
}
