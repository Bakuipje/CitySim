// Fill out your copyright notice in the Description page of Project Settings.

#include "Labourers.h"
#include "GOAP/GOAPBase.h"
#include "InverntoryComponent.h"
#include "interactables/InvertoryBase.h"

ALabourers::ALabourers()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ALabourers::BeginPlay()
{
	Super::BeginPlay();
}
void ALabourers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
TSet<TPair<EGoapIdentifier, bool>> ALabourers::GetWorldState()
{
	 TSet<TPair<EGoapIdentifier, bool>> worldData = TSet<TPair<EGoapIdentifier, bool>>();
	 UInverntoryComponent* inventoryComp = FindComponentByClass<UInverntoryComponent>();
	 worldData.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Water, inventoryComp->GetInventory(waterClass) > 0));
	 worldData.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Key, inventoryComp->GetInventory(KeyClass) > 0));
	 return worldData;
}

TSet<TPair<EGoapIdentifier, bool>> ALabourers::CreateGoalState()
{
	return TSet<TPair<EGoapIdentifier, bool>>();
}
void ALabourers::PlanFailed(TSet<TPair<EGoapIdentifier, bool>> failedGoal)
{
}
void ALabourers::PlanFound(TSet<TPair<EGoapIdentifier, bool>> goal, TQueue<UGOAPBase*>* actions)
{
}
void ALabourers::ActionsFinished()
{
}
void ALabourers::PlanAborted(UGOAPBase* aborter)
{
}
bool ALabourers::MoveAgent(UGOAPBase* nextAction)
{
	if (nextAction == nullptr)return false;
	MoveTo(nextAction->target->GetActorLocation());
	if (IsNear(GetActorLocation(), nextAction->target->GetActorLocation(), 200))
	{
		nextAction->SetInRange(true);
		return true;
	}
	return false;
}