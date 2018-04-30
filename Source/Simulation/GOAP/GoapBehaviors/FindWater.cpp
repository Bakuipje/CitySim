// Fill out your copyright notice in the Description page of Project Settings.

#include "FindWater.h"
#include "GOAP/GOAPBase.h"
#include "interactables/StorageBase.h"
#include "Agent.h"
#include "EngineUtils.h"
#include "MoodComponent.h"
#include "GOAP/Labourers/workComponent.h"
#include "interactables/InvertoryBase.h"
#include "InverntoryComponent.h"

UFindWater::UFindWater()
{
	AddPreconditions(EGoapIdentifier::GI_Water, false);
	AddEffects(EGoapIdentifier::GI_Water, true);
}

UFindWater::~UFindWater()
{}

void UFindWater::Reset()
{
	Super::Reset();

	found = false;
	waterStorage = nullptr;
	target = nullptr;

}

bool UFindWater::IsDone()
{
	return found;
}
bool UFindWater::RequireInrange()
{
	return true;
}
bool UFindWater::CheckProceduralPrecondition(AAgent* agent)
{
	UworkComponent* gardener = (UworkComponent*)agent->GetComponentByClass(UworkComponent::StaticClass());
	float currentDistsqr = 1e34f;
	AStorageBase* newActor = nullptr;
	for (TActorIterator<AStorageBase>actoritr(agent->GetWorld()); actoritr; ++actoritr)
	{
		AStorageBase* currentAgent = *actoritr;
		if (currentAgent->IsA(gardener->waterstorageClass) && currentAgent->GetInteractable(gardener->waterClass)!= nullptr)
		{
			if (currentDistsqr > FVector::DistSquared(agent->GetActorLocation(), currentAgent->GetActorLocation()))
			{
				currentDistsqr = FVector::DistSquared(agent->GetActorLocation(), currentAgent->GetActorLocation());
				newActor = *actoritr;
			}
		}
	}
	if (newActor != nullptr)
	{
		waterStorage = (AStorageBase*)newActor;
		agent->currentStorage = waterStorage;
		target = waterStorage;
		agent->GetMoodComponent()->AddThinkingString(FString("found water"));
	}
	return newActor != nullptr;
}
bool UFindWater::Perform(AAgent* agent)
{
	UworkComponent* gardener = (UworkComponent*)agent->GetComponentByClass(UworkComponent::StaticClass());
	UInverntoryComponent* inventory = (UInverntoryComponent*)agent->GetComponentByClass(UInverntoryComponent::StaticClass());
	AInvertoryBase* water = (AInvertoryBase*)((AStorageBase*)target)->GetInteractable(gardener->waterClass);
	agent->GetMoodComponent()->AddThinkingString(FString("performing collecting water"));
	if (water == nullptr)return false;
	inventory->AddInventroy(water, 1);
	//((AStorageBase*)target)->RemoveInteractable(gardener->waterClass);
	found = true;
	return true;
}