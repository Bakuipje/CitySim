// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveState.h"
#include "FiniteStateMachine.h"
#include "Agent.h"
#include "MoodComponent.h"
#include "IdleState.h"
#include "GOAP/GOAPBase.h"
#include "GOAP/GoapComponent.h"
#include "GOAP/GoapInterface.h"
#include "GOAP/GOAPPlanner.h"

void UMoveState::Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent)
{
	UGOAPBase* action = nullptr;
	goapComponent->currentActions->Peek(action);
	if (action != nullptr&& action->RequireInrange() && action->target == nullptr)
	{
		fsm->PopState();
		fsm->PopState();
		UIdleState* idleState = NewObject<UIdleState>();
		fsm->PushState(idleState);
		return;
	}
	if (goapComponent->dataProvider->MoveAgent(action))
	{
		fsm->PopState();
	}
}

