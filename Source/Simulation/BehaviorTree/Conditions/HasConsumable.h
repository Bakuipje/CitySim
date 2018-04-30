// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"
#include <SubclassOf.h>
#include "HasConsumable.generated.h"

/**
 * 
 */
class AInvertoryBase;
UCLASS()
class SIMULATION_API UHasConsumable:public URGCondition
{
	GENERATED_BODY()

public:
	UHasConsumable();
	~UHasConsumable();
	UHasConsumable(URGBehaviorTreeComponent* ownerComp, TSubclassOf<AInvertoryBase> inventoryType);

	virtual bool Execute_Implementation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInvertoryBase> m_inventoryType;
};
