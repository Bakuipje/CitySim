// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Queue.h>
#include "GOAPBase.h"
#include "GOAPPlanner.generated.h"

/**
 * 
 */
class UGOAPBase;
class AAgent;
class Node;

UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API UGOAPPlanner: public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UGOAPPlanner();
	~UGOAPPlanner();
	TQueue<UGOAPBase*>* Plan(AAgent* agent, TSet<UGOAPBase*> availableActions, TSet<TPair<EGoapIdentifier, bool>> worldState, TSet<TPair<EGoapIdentifier, bool>> goal);

private:
	bool buildGraph(Node* parent, TArray<Node*>& leaves, TSet<UGOAPBase*> usableActions, TSet<TPair<EGoapIdentifier, bool>> goal);
	TSet<UGOAPBase*> ActionSubset(TSet<UGOAPBase*> actions, UGOAPBase* removeMe);
	bool Instate(TSet < TPair<EGoapIdentifier, bool>> test, TSet<TPair<EGoapIdentifier, bool>>* state);
	TSet<TPair<EGoapIdentifier, bool>> *populateState(TSet<TPair<EGoapIdentifier, bool>>*currentState, TSet<TPair<EGoapIdentifier, bool>>*stateChange);
		
};
/*
class Node
{
public:
	Node* parent;
	float runningCost;
	TSet<TPair<FName, UObject>>state;
	UGOAPBase action;
	public Node(Node* parent, float runningCost, TSet<TPair<FName, UObject>> state, UGOAPBase action)
	{
		this->parent = parent;
		this->runningCost = runningCost;
		this->state = state;
		this->action = action;
	}
};*/

