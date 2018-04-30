// Fill out your copyright notice in the Description page of Project Settings.

#include "HasHome.h"
#include "Agent.h"
#include "Building/House.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"


bool UHasHome::Execute_Implementation()
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if(agent->homePlace!= nullptr)
		agent->moveLocation.Insert( agent->homePlace,0);
	return agent->homePlace!= nullptr;
}
