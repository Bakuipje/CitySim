// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "GymBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UGymBehavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()
	
public:
	virtual EBehaviorState Tick_Implementation(float deltaTime);

	float gymDuration;
	float gymTimer=0;
	virtual void Init();
	
	
};