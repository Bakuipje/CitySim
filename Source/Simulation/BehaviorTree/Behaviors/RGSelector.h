// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGSelector.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API URGSelector: public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	URGSelector();
	~URGSelector();
	URGSelector(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost);

	virtual EBehaviorState Tick_Implementation(float deltaTime);
};
