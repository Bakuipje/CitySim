// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGQueue.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API URGQueue:public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	URGQueue();
	URGQueue(URGBehaviorTreeComponent*ownerComp,   TArray<URGBehaviorTreeBase*>children, int cost);
	~URGQueue();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	virtual void Reset();
	int m_lowestCost = 0;
};
