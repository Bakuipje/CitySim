// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "FailedFood.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UFailedFood : public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	EBehaviorState Tick_Implementation(float deltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int stressAmount;
	
	
	
};
