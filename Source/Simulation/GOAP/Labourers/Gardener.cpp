// Fill out your copyright notice in the Description page of Project Settings.

#include "Gardener.h"
#include "GOAP/GoapComponent.h"
#include "GOAP/FSM/IdleState.h"
#include "GOAP/FSM/FiniteStateMachine.h"

AGardener::AGardener()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AGardener::BeginPlay()
{
	Super::BeginPlay();
}
void AGardener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
TSet<TPair<EGoapIdentifier, bool>> AGardener::CreateGoalState()
{
	TSet<TPair<EGoapIdentifier, bool>> goal = TSet<TPair<EGoapIdentifier, bool>>();
	goal.Add(TPair<EGoapIdentifier, bool>(EGoapIdentifier::GI_Water, true));
	return goal;
}

void AGardener::ActionsFinished()
{

}