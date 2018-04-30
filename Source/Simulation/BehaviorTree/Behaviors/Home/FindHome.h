// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "FindHome.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UFindHome : public URGBehaviorTreeBase
{
	GENERATED_BODY()
	
public:
	virtual EBehaviorState Tick_Implementation(float deltaTime);

	
};
