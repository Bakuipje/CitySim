// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "WorkBehavior.generated.h"

/**
 * 
 */
class AAgent;
UCLASS()
class SIMULATION_API UWorkBehavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()
	
public:
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	virtual void Reset();
	virtual void BeginPlay();
	virtual void Init();
	void FindBetterWork(AAgent* agent);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float workDuration;
	float workTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int compensation;
	
	
};
