// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine.generated.h"
/**
 *
 */
class UFSMState;
class AAgent;
class UGoapComponent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API UFiniteStateMachine: public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UFiniteStateMachine();
	~UFiniteStateMachine();
	void Update(UGoapComponent* goapComponent,float deltaTime, AAgent* agent );
	void PushState(UFSMState* state);
	void PopState();
private:
	UPROPERTY()
	TArray<UFSMState*> stateList;
};
