// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include <SubclassOf.h>
#include "FindStorage.generated.h"

/**
 * 
 */
class AStorageBase;
UCLASS()
class SIMULATION_API UFindStorage: public URGBehaviorTreeBase
{
	GENERATED_BODY()
public:
	UFindStorage();
	UFindStorage(URGBehaviorTreeComponent* ownercomp, TArray<URGBehaviorTreeBase*> children, int cost, float range);
	~UFindStorage();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AStorageBase> m_storageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_range;
};
