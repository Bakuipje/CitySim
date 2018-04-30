// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Queue.h>
#include <interface.h>
#include "GOAP/GOAPBase.h"
#include "GoapInterface.generated.h"
// This class does not need to be modified.
class UGOAPBase;
UINTERFACE(MinimalAPI)
class UGoapInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMULATION_API IGoapInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TSet<TPair<EGoapIdentifier, bool>> GetWorldState() = 0;
	virtual TSet<TPair<EGoapIdentifier, bool>> CreateGoalState() = 0;
	virtual void PlanFailed(TSet<TPair<EGoapIdentifier, bool>> failedGoal)=0;
	virtual void PlanFound(TSet<TPair<EGoapIdentifier, bool>> goal, TQueue<UGOAPBase*>* actions) = 0;
	virtual void ActionsFinished() = 0;
	virtual void PlanAborted(UGOAPBase* aborter) = 0;
	virtual bool MoveAgent(UGOAPBase* nextAction)=0;
};
