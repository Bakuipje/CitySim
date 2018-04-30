// Fill out your copyright notice in the Description page of Project Settings.

#include "FindConsumable.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "EngineUtils.h"
#include "interactables/StorageBase.h"
#include "interactables/invertoryBase.h"

UFindConsumable::UFindConsumable()
{
}
UFindConsumable::UFindConsumable(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase *> children, int cost,TSubclassOf<AInvertoryBase> invertoryType,float range)
	:URGBehaviorTreeBase(ownerComp, children, cost), m_range(range), m_invertoryType(invertoryType)
{}
UFindConsumable::~UFindConsumable()
{
}
EBehaviorState UFindConsumable::Tick_Implementation(float deltaTime)
{
	float currentDistsqr = 1e34f;
	AStorageBase* newActor = nullptr;
	for (TActorIterator<AStorageBase>actoritr(m_ownerComp->GetWorld()); actoritr; ++actoritr)
	{
		AStorageBase* currentAgent = *actoritr;
		if(!currentAgent->HasInteractable(m_invertoryType))
			continue;
		float distsqr = FVector::DistSquared(m_ownerComp->GetOwner()->GetActorLocation(), currentAgent->GetActorLocation());
		if (currentDistsqr > distsqr)
		{
			currentDistsqr = distsqr;
			newActor = *actoritr;
		}
	}
	if (newActor != nullptr)
	{
		((AAgent*)m_ownerComp->GetOwner())->currentStorage = (AStorageBase*)newActor;
		behaviorState = EBehaviorState::EB_Succeed;
	}
	else behaviorState = EBehaviorState::EB_Failed;
	return behaviorState;

}