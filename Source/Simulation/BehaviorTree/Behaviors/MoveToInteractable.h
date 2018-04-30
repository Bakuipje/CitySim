// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "MoveToInteractable.generated.h" 

/**
 * 
 */
class AStorageBase;
UCLASS()
class SIMULATION_API UMoveToInteractable: public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UMoveToInteractable();
	~UMoveToInteractable();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	EBehaviorState MoveToDestination(float deltaTime);
	EBehaviorState MoveToStorage(float deltaTime);
	AActor* m_destinationObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_range = 100;
};
