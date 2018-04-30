// Fill out your copyright notice in the Description page of Project Settings.

#include "workComponent.h"
#include "Agent.h"
#include "GOAP/GOAPBase.h"
#include "InverntoryComponent.h"
#include "interactables/InvertoryBase.h"

// Sets default values for this component's properties
UworkComponent::UworkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UworkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UworkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSet<TPair<EGoapIdentifier, bool>> UworkComponent::GetWorldState()
{
	TSet<TPair<EGoapIdentifier, bool>> worldData = TSet<TPair<EGoapIdentifier, bool>>();
	UInverntoryComponent* inventoryComp = GetOwner()->FindComponentByClass<UInverntoryComponent>();
	worldData.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Water, inventoryComp->GetInventory(waterClass) > 0));
	worldData.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Key, inventoryComp->GetInventory(KeyClass) > 0));
	return worldData;
}

TSet<TPair<EGoapIdentifier, bool>> UworkComponent::CreateGoalState()
{
	TSet<TPair<EGoapIdentifier, bool>> goal = TSet<TPair<EGoapIdentifier, bool>>();
	goal.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Water, true));
	return goal;
}
void UworkComponent::PlanFailed(TSet<TPair<EGoapIdentifier, bool>> failedGoal)
{
}
void UworkComponent::PlanFound(TSet<TPair<EGoapIdentifier, bool>> goal, TQueue<UGOAPBase*>* actions)
{
}
void UworkComponent::ActionsFinished()
{
}
void UworkComponent::PlanAborted(UGOAPBase* aborter)
{
}
bool UworkComponent::MoveAgent(UGOAPBase* nextAction)
{
	if (nextAction == nullptr)return false;
	AAgent* owner = (AAgent*)GetOwner();
	owner->MoveTo(nextAction->target->GetActorLocation());
	if (owner->IsNear(owner->GetActorLocation(), nextAction->target->GetActorLocation(), 200))
	{
		nextAction->SetInRange(true);
		return true;
	}
	return false;
}

