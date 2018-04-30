// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGTimer.generated.h"
/**
*
*/
UCLASS()
class SIMULATION_API URGTimer :public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	URGTimer();
	//URGTimer(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*>children, int cost, float time);
	~URGTimer();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	virtual void Reset();
	virtual void BeginPlay();
	float m_timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_time;
};
