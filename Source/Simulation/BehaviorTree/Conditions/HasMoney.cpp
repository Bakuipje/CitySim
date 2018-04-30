// Fill out your copyright notice in the Description page of Project Settings.

#include "HasMoney.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"


bool UHasMoney::Execute_Implementation()
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	return agent->budget > requiredAmount;
}
