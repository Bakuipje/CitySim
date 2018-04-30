// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "LiesureBehavior.generated.h"

/**
 * 
 */
class AAgent;
UCLASS()
class SIMULATION_API ULiesureBehavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	virtual EBehaviorState Tick_Implementation(float deltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float liesureDuration;
	float liesureTimer;
	virtual void Reset();
	virtual void BeginPlay();
	
	
	
};
