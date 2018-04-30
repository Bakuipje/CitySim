// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "FoodBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UFoodBehavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	EBehaviorState Tick_Implementation(float deltaTime);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float foodDuration;
	float foodTimer;
	virtual void Reset();
	virtual void Init();
	virtual void BeginPlay();
	
};
