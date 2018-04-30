// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "DrinkBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UDrinkBehavior:public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UDrinkBehavior();
	UDrinkBehavior(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost);
	~UDrinkBehavior();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
};
