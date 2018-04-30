// Fill out your copyright notice in the Description page of Project Settings.

#include "GoapComponent.h"
#include "FSM/FiniteStateMachine.h"
#include "FSM/FSMState.h"
#include "GOAPBase.h"
#include "GOAPPlanner.h"
#include "GoapInterface.h"
#include "Agent.h"
#include "GOAP/Labourers/workComponent.h"
#include "FSM/IdleState.h"

// Sets default values for this component's properties
UGoapComponent::UGoapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGoapComponent::PostInit()
{

	stateMachine = NewObject< UFiniteStateMachine>();
	availableActions = TSet<UGOAPBase*>();
	currentActions = new TQueue<UGOAPBase*>();
	planner =   NewObject< UGOAPPlanner>();
	LoadActions();
	FindDataProvider();
	CreateIdleState();
	CreateMoveState();
	CreatePerformAction();
	idleState = NewObject<UIdleState>();

	stateMachine->PushState(idleState);
}


// Called every frame
void UGoapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(stateMachine!= nullptr&& activate)
		stateMachine->Update(this,DeltaTime, (AAgent*)GetOwner());
	// ...
}

void UGoapComponent::AddAction(UGOAPBase* action)
{
	availableActions.Add(action);
}

UGOAPBase* UGoapComponent::GetAction(TSubclassOf<UGOAPBase> actionType)
{
	TArray<UGOAPBase*> availableActionsArray = availableActions.Array();
	for (int i=0; i<availableActionsArray.Num(); i++)
	{
		if (availableActionsArray[i]->GetClass() == actionType)
			return availableActionsArray[i];
	}
	return nullptr;
}

void UGoapComponent::RemoveAction(UGOAPBase* action)
{
	availableActions.Remove(action);
}

bool UGoapComponent::HasActionPlan()
{
	return !currentActions->IsEmpty();
}

void UGoapComponent::CreateIdleState()
{
	idleState = NewObject<UIdleState>();
	TSet<TPair<EGoapIdentifier, bool>> worlDstate = dataProvider->GetWorldState();
	TSet<TPair<EGoapIdentifier, bool>> goal = dataProvider->CreateGoalState();

	TQueue<UGOAPBase*>* plan = planner->Plan((AAgent*)GetOwner(), availableActions, worlDstate, goal);
	if (plan != nullptr)
	{
		currentActions = plan;
		dataProvider->PlanFound(goal, plan);

		stateMachine->PopState();
		CreatePerformAction();
		stateMachine->PushState(performActionState);
	}
	else
	{
		dataProvider->PlanFailed(goal);
		stateMachine->PopState();
		stateMachine->PushState(idleState);
	}
}

void UGoapComponent::CreateMoveState()
{
	moveToState = NewObject<UFSMState>();

	UGOAPBase* action = nullptr;
	currentActions->Peek(action);
	if (action!= nullptr&& action->RequireInrange() && action->target == nullptr)
	{
		stateMachine->PopState();
		stateMachine->PopState();
		stateMachine->PushState(idleState);
		return;
	}
	if (dataProvider->MoveAgent(action))
	{
		stateMachine->PopState();
	}
}

void UGoapComponent::CreatePerformAction()
{
	performActionState = NewObject<UFSMState>();
	if (!HasActionPlan())
	{
		stateMachine->PopState();
		stateMachine->PushState(idleState);

	}
	UGOAPBase* action = nullptr;
	currentActions->Peek(action);
	if (action!= nullptr && action->IsDone())
	{
		currentActions->Dequeue(action);
	}
	if (HasActionPlan())
	{
		currentActions->Peek(action);
		bool inRange = action->RequireInrange() ? action->IsinRange() : true;

		if (inRange)
		{
			bool succes = action->Perform((AAgent*)GetOwner());
			if (!succes)
			{
				stateMachine->PopState();
				stateMachine->PushState(idleState);
				dataProvider->PlanAborted(action);
			}
		}
		else 
		{
			CreateMoveState();
			stateMachine->PushState(moveToState);
		}
	}
	else
	{
		stateMachine->PopState();
		stateMachine->PushState(idleState);
		dataProvider->ActionsFinished();
	}
}

void UGoapComponent::FindDataProvider()
{
	//GetOwner()->GetClass()->
	dataProvider = Cast<IGoapInterface>(GetOwner()->GetComponentByClass(UworkComponent::StaticClass()));
}
void UGoapComponent::LoadActions()
{
	for (int i = 0; i < goapActions.Num(); i++)
	{
		availableActions.Add(goapActions[i]);
	}
}