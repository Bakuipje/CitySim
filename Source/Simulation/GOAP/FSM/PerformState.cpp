// Fill out your copyright notice in the Description page of Project Settings.

#include "PerformState.h"

#include "FiniteStateMachine.h"
#include "Agent.h"
#include "IdleState.h"
#include "MoveState.h"
#include "GOAP/GOAPBase.h"
#include "GOAP/GoapComponent.h"
#include "GOAP/GoapInterface.h"
#include "GOAP/GOAPPlanner.h"

void UPerformState::Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent)
{
	UIdleState* idleState = NewObject<UIdleState>();
	UMoveState* moveToState = NewObject<UMoveState>();

	if (!goapComponent->HasActionPlan())
	{
		fsm->PopState();
		fsm->PushState(idleState);

	}
	UGOAPBase* action = nullptr;
	goapComponent->currentActions->Peek(action);
	if (action != nullptr && action->IsDone())
	{
		goapComponent->currentActions->Dequeue(action);
	}
	if (goapComponent->HasActionPlan())
	{
		goapComponent->currentActions->Peek(action);
		bool inRange = action->RequireInrange() ? action->IsinRange() : true;

		if (inRange)
		{
			bool succes = action->Perform((AAgent*)goapComponent->GetOwner());
			if (!succes)
			{
				fsm->PopState();
				fsm->PushState(idleState);
				goapComponent->dataProvider->PlanAborted(action);
			}
		}
		else
		{
			fsm->PushState(moveToState);
		}
	}
	else
	{
		fsm->PopState();
		fsm->PushState(idleState);
		goapComponent->dataProvider->ActionsFinished();
	}
}


