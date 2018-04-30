// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include <SubclassOf.h>
#include "PickConsumable.generated.h"

/**
 * 
 */
class AInteractableBase;
UCLASS()
class SIMULATION_API UPickConsumable:public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UPickConsumable();
	UPickConsumable(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost, TSubclassOf<AInteractableBase> inventoryType);
	~UPickConsumable();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInteractableBase> m_invertoryType;
};
