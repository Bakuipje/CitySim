// Fill out your copyright notice in the Description page of Project Settings.

#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "Agent.h"
#include "GOAP/GoapComponent.h"

UFiniteStateMachine::UFiniteStateMachine()
{
}
UFiniteStateMachine::UFiniteStateMachine(FObjectInitializer const& ObjectInitializer)
{}
UFiniteStateMachine::~UFiniteStateMachine()
{
}

void UFiniteStateMachine::Update(UGoapComponent* goapComponent,float deltaTime, AAgent* agent)
{
	if (stateList.Num() > 0)
		stateList[0]->Update(goapComponent,deltaTime, this, agent);
}

void UFiniteStateMachine::PushState(UFSMState* state)
{
	
	stateList.Insert(state,0);
}

void UFiniteStateMachine::PopState()
{
	if(stateList.Num()>0)
	stateList.RemoveAt(0);
}