// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/GOAPBase.h"

/**
 * 
 */
class UGOAPBase;
class SIMULATION_API Node
{
public:

public:
	Node();
	~Node();
	Node(Node* parent, float runningCost, TSet<TPair<EGoapIdentifier, bool>>* state, UGOAPBase* action);
	Node* parent;
	float runningCost;
	TSet<TPair<EGoapIdentifier, bool>>*state;
	UGOAPBase* action;


};
