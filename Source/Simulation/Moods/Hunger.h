// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoodBase.h"
#include "Hunger.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class SIMULATION_API UHunger:public UMoodBase
{
	GENERATED_BODY()
public:
	UHunger();
	~UHunger();
	virtual URGBehaviorTreeBase* GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent ) ;
};
