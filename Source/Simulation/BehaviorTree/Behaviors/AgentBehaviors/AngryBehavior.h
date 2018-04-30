// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "AngryBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UAngryBehavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	EBehaviorState Tick_Implementation(float deltaTime);
	virtual void Reset();
	virtual void BeginPlay(); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int stressAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float argueTime;
	float argueTimer;
	UPROPERTY()
		class AAgent* target;
	
	
	
};
