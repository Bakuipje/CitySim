// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "MovementBehavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UMovementBehavior : public URGSelector
{
	GENERATED_BODY()
public:
	UMovementBehavior();
	virtual URGBehaviorTreeBase* GetBehaviorTreeSegment(URGBehaviorTreeComponent* owner);

	AActor* destinationActor;
	
};
