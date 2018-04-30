// Fill out your copyright notice in the Description page of Project Settings.

#include "IdleState.h"
#include "Agent.h"
#include "PerformState.h"
#include "FiniteStateMachine.h"
#include "GOAP/GoapComponent.h"
#include "GOAP/GoapInterface.h"
#include "GOAP/GOAPPlanner.h"

void UIdleState::Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent)
{
	TSet<TPair<EGoapIdentifier, bool>> worlDstate = goapComponent->dataProvider->GetWorldState();
	TSet<TPair<EGoapIdentifier, bool>> goal = goapComponent->dataProvider->CreateGoalState();

	TQueue<UGOAPBase*>* plan = goapComponent->planner->Plan((AAgent*)goapComponent->GetOwner(), goapComponent->availableActions, worlDstate, goal);
	if (plan != nullptr)
	{
		goapComponent->currentActions = plan;
		goapComponent->dataProvider->PlanFound(goal, plan);

		fsm->PopState();
		UPerformState* performActionState = NewObject<UPerformState>();
		fsm->PushState(performActionState);
	}
	else
	{
		goapComponent->dataProvider->PlanFailed(goal);
		fsm->PopState();
		UIdleState* idleState = NewObject<UIdleState>();
		fsm->PushState(idleState);
	}
}




