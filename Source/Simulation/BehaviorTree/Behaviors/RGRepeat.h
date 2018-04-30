// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGRepeat.generated.h"
/**
 * 
 */
class URGCondition;
UCLASS()
class SIMULATION_API URGRepeat:public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	URGRepeat();
	URGRepeat(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children,int cost, TArray<URGCondition*> conditions);
	~URGRepeat();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	TArray<URGCondition*> m_conditions;
};
