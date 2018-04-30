// Fill out your copyright notice in the Description page of Project Settings.

#include "FindStorage.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "EngineUtils.h"
#include "interactables/StorageBase.h"

UFindStorage::UFindStorage()
{
}
UFindStorage::UFindStorage(URGBehaviorTreeComponent* ownercomp, TArray<URGBehaviorTreeBase*> children, int cost, float range)
	:URGBehaviorTreeBase(ownercomp, children, cost), m_range(range)
{
}


UFindStorage::~UFindStorage()
{
}

EBehaviorState UFindStorage::Tick_Implementation(float deltaTime)
{
	float currentDistsqr = 1e34f;
	AStorageBase* newActor = nullptr;
	for (TActorIterator<AStorageBase>actoritr(m_ownerComp->GetWorld()); actoritr; ++actoritr)
	{
		AStorageBase* currentAgent = *actoritr;
		if(currentAgent->IsA(m_storageType))
		if (currentDistsqr >  FVector::DistSquared(m_ownerComp->GetOwner()->GetActorLocation(), currentAgent->GetActorLocation()))
		{
			currentDistsqr = FVector::DistSquared(m_ownerComp->GetOwner()->GetActorLocation(), currentAgent->GetActorLocation());
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