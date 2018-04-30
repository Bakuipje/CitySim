// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include <SubclassOf.h>
#include "EatBehavior.generated.h"

/**
 * 
 */
class UMoodBase;
UCLASS()
class SIMULATION_API UEatBehavior:public URGBehaviorTreeBase
{
	GENERATED_BODY()

public:
	UEatBehavior();
	UEatBehavior(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children,int cost);
	~UEatBehavior();
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMoodBase> m_moodType;
};
