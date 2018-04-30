// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterPlant.h"
#include "GOAP/GOAPBase.h"
#include "interactables/StorageBase.h"
#include "Agent.h"
#include "EngineUtils.h"
#include "GOAP/Labourers/Labourers.h"
#include "GOAP/Labourers/workComponent.h"
#include "interactables/InvertoryBase.h"
#include "InverntoryComponent.h"

UWaterPlant::UWaterPlant()
{
	AddPreconditions(EGoapIdentifier::GI_Water, true);
	AddEffects(EGoapIdentifier::GI_Water, false);
	AddEffects(EGoapIdentifier::GI_Key, true);
}

UWaterPlant::~UWaterPlant()
{}

void UWaterPlant::Reset()
{
	Super::Reset();
	found = false;
	plantStorage = nullptr;
}

bool UWaterPlant::IsDone()
{
	return found;
}
bool UWaterPlant::RequireInrange()
{
	return true;
}
bool UWaterPlant::CheckProceduralPrecondition(AAgent* agent)
{
	// get GOAP Component
	UworkComponent* gardener = (UworkComponent*)agent->GetComponentByClass(UworkComponent::StaticClass());
	float currentDistsqr = 1e34f;
	AStorageBase* newActor = nullptr;
	// search for a plant that needs watering
	for (TActorIterator<AStorageBase>actoritr(agent->GetWorld()); actoritr; ++actoritr)
	{
		AStorageBase* currentAgent = *actoritr;
		if (currentAgent->IsA(gardener->plantStorageClass) && !currentAgent->used)
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
		// found a plant 
		plantStorage = (AStorageBase*)newActor;
		agent->currentStorage = plantStorage;
		plantStorage->used = true;
		target = plantStorage;
	}
	return newActor != nullptr;
}
bool UWaterPlant::Perform(AAgent* agent)
{
	UworkComponent* gardener = (UworkComponent*)agent->GetComponentByClass(UworkComponent::StaticClass());
	UInverntoryComponent* inventory = (UInverntoryComponent*)agent->GetComponentByClass(UInverntoryComponent::StaticClass());
	// remove the water from the agents inventory
	inventory->RemoveInventory(gardener->waterClass, 1);
	// execute the watering of the plant
	plantStorage->used = true;
	found = true;
	return true;
}



