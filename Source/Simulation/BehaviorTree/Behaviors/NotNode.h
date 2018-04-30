// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "NotNode.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API UNotNode:public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UNotNode();
	~UNotNode();
	virtual EBehaviorState Tick(float deltaTime);

};
