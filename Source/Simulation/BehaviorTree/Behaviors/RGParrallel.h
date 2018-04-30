// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGParrallel.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API URGParrallel: public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	URGParrallel();
	~URGParrallel();

	virtual EBehaviorState Tick_Implementation(float deltaTime);
};
