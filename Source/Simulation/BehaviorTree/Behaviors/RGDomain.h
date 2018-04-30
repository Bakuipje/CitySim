// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "RGDomain.generated.h"

/**
 * 
 */
class URGCondition;
UCLASS()
class SIMULATION_API URGDomain:public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	URGDomain();
	~URGDomain();
	//URGDomain(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost, TArray<RGCondition*>conditions);

	virtual EBehaviorState Tick_Implementation(float deltaTime);
	virtual void Reset();
	virtual void BeginPlay();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<URGCondition*> m_conditions;
	bool m_checkedConditions;
};
