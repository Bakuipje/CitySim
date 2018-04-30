// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include <SubclassOf.h>
#include "FindConsumable.generated.h"

/**
 * 
 */
class AInvertoryBase;
UCLASS()
class SIMULATION_API UFindConsumable: public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UFindConsumable();
	UFindConsumable(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost, TSubclassOf<AInvertoryBase> invertoryType,float m_range);
	~UFindConsumable();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInvertoryBase> m_invertoryType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_range;
};
