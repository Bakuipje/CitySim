// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGSequence.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API URGSequence:public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	URGSequence();
	URGSequence(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost);

	~URGSequence();
	virtual EBehaviorState Tick_Implementation(float deltaTime);

};
