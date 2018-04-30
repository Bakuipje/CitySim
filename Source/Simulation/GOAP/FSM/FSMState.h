// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.generated.h"

/**
 * 
 */
class UFiniteStateMachine;
class AAgent;
class UGoapComponent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API UFSMState:public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UFSMState();
	~UFSMState();
	virtual void Update(UGoapComponent* goapComponent,float deltaTime, UFiniteStateMachine* fsm, AAgent* agent);
};
