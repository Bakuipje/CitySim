// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPPlanner.h"
#include "Agent.h"
#include "GOAPBase.h"
#include "Node.h"
UGOAPPlanner::UGOAPPlanner()
{
}

UGOAPPlanner::UGOAPPlanner(FObjectInitializer const& ObjectInitializer)
{
}

UGOAPPlanner::~UGOAPPlanner()
{
}

TQueue<UGOAPBase*>*  UGOAPPlanner::Plan(AAgent* agent, TSet<UGOAPBase*> availableActions, TSet<TPair<EGoapIdentifier, bool>> worldState, TSet<TPair<EGoapIdentifier, bool>> goal)
{
	TArray<UGOAPBase*> actionArray = availableActions.Array();
	for (int i = 0; i < actionArray.Num(); i++)
	{
		actionArray[i]->Reset();
	}
	TSet<UGOAPBase*> usableActions = TSet<UGOAPBase*>();
	for (int i = 0; i < actionArray.Num(); i++)
	{
		if (actionArray[i]->CheckProceduralPrecondition(agent))
			usableActions.Add(actionArray[i]);
	}
	TArray<Node*> leaves =  TArray<Node*>();
	Node*start = new Node(nullptr, 0, &worldState, nullptr);
	bool succes = buildGraph(start, leaves, usableActions, goal);

	if (!succes)
		return nullptr;

	Node* cheapest = nullptr;
	for (int i = 0; i < leaves.Num(); i++)
	{
		if (cheapest == nullptr)
			cheapest = leaves[i];
		else
		{
			if (leaves[i]->runningCost < cheapest->runningCost)
				cheapest = leaves[i];
		}
	}

	TArray<UGOAPBase*> result = TArray<UGOAPBase *>();
	Node* n = cheapest;
	while (n != nullptr)
	{
		if (n->action != nullptr)
			result.Insert(n->action, 0);

		n = n->parent;
	}

	TQueue<UGOAPBase*>* queue = new TQueue<UGOAPBase*>();
	for (int i = 0; i < result.Num(); i++)
		queue->Enqueue(result[i]);
	return queue;
}

bool UGOAPPlanner::buildGraph(Node* parent, TArray<Node *> &leaves, TSet<UGOAPBase *> usableActions, TSet<TPair<EGoapIdentifier, bool>> goal)
{
	bool foundOne = false;
	TArray<UGOAPBase*> actionArray = usableActions.Array();
	for (int i = 0;i< actionArray.Num(); i++)
	{
		if (Instate(*actionArray[i]->preconditions, parent->state))
		{
			TSet<TPair<EGoapIdentifier, bool>>*currentState = populateState(parent->state, actionArray[i]->effects);

			Node* node = new Node(parent, parent->runningCost + actionArray[i]->cost, currentState, actionArray[i]);
			if (Instate(goal, currentState))
			{
				leaves.Add(node);
				foundOne = true;
			}
			else
			{
				TSet<UGOAPBase*> subset = ActionSubset(usableActions, actionArray[i]);
				bool found = buildGraph(node, leaves, subset, goal);
				if (found)
					foundOne = true;
			}
		}
	}
	return foundOne;
}

TSet<UGOAPBase*> UGOAPPlanner::ActionSubset(TSet<UGOAPBase *> actions, UGOAPBase* removeMe)
{
	TSet<UGOAPBase*> subset = TSet<UGOAPBase*>();
	TArray<UGOAPBase*> actionArray = actions.Array();
	for (int i = 0; i < actionArray.Num(); i++)
	{
		if (actionArray[i] != removeMe)
			subset.Add(actionArray[i]);
	}
	return subset;
}

bool UGOAPPlanner::Instate(TSet<TPair<EGoapIdentifier, bool>>test, TSet<TPair<EGoapIdentifier, bool>>* state)
{
	bool allmatch = true;
	TArray<TPair<EGoapIdentifier, bool>>testArray = test.Array();
	TArray<TPair<EGoapIdentifier, bool>>statetArray = state->Array();
	for (int i = 0; i < testArray.Num(); i++)
	{
		bool match = false;
		for (int j = 0; j < statetArray.Num(); j++)
		{
			if (statetArray[j] == testArray[i])
			{
				match = true;
				break;
			}
		}
		if (!match)
			allmatch = false;
	}
	return allmatch;
}
TSet<TPair<EGoapIdentifier, bool>>* UGOAPPlanner::populateState(TSet<TPair<EGoapIdentifier, bool>>*currentState, TSet<TPair<EGoapIdentifier, bool>>*stateChange)
{
	TSet<TPair<EGoapIdentifier, bool>>* state = new TSet<TPair<EGoapIdentifier, bool>>();
	TArray<TPair<EGoapIdentifier, bool>>currentStateArray = currentState->Array();
	TArray<TPair<EGoapIdentifier, bool>>stateChangeArray = stateChange->Array();

	for (int i = 0; i < currentStateArray.Num(); i++)
	{
		state->Add(currentStateArray[i]);
	}
	TArray<TPair<EGoapIdentifier, bool>>stateArray = state->Array();

	for (int i = 0; i < stateChangeArray.Num(); i++)
	{
		bool exist = false;
		for (int j = 0; j < stateArray.Num(); j++)
		{
			if (stateArray[j] == stateChangeArray[i])
			{
				exist = true;
				break;
			}
		}
		if (exist)
		{
			TPair<EGoapIdentifier, bool>* kvp = nullptr;
			int index = -1;
			for (int j = 0; j < stateArray.Num(); j++)
			{
				if (stateArray[j].Key == stateChangeArray[i].Key)
					kvp = &stateArray[j];
			}
			if (index != -1)
				state->Remove(*kvp);
			TPair<EGoapIdentifier, bool> *updated = new TPair<EGoapIdentifier, bool>(stateChangeArray[i].Key, stateChangeArray[i].Value);
			state->Add(*updated);
		}
		else
		{
			state->Add(stateChangeArray[i]);
		}
	}
	return state;

}

