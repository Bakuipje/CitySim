// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "MoveToBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UMoveToBehavior: public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UMoveToBehavior();
	UMoveToBehavior(URGBehaviorTreeComponent* ownercomp, TArray<URGBehaviorTreeBase*> children,int cost,FVector m_destination, float range);
	~UMoveToBehavior();
	virtual EBehaviorState Tick_Implementation(float deltaTime);

	FVector m_destination;
	float m_range;
};
