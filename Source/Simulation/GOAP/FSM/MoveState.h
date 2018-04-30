// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/FSM/FSMState.h"
#include "MoveState.generated.h"

/**
 * 
 */
class UFiniteStateMachine;
class AAgent;
class UGoapComponent;
UCLASS()
class SIMULATION_API UMoveState : public UFSMState
{
	GENERATED_BODY()
	
public:
	virtual void Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent)override;

	
	
};
