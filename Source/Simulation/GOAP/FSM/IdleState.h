// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/FSM/FSMState.h"
#include "IdleState.generated.h"

/**
 * 
 */
class UFiniteStateMachine;
class AAgent;
UCLASS()
class SIMULATION_API UIdleState : public UFSMState
{
	GENERATED_BODY()
	
public:
	virtual void Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent)override;

	
	
};
