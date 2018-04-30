// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moods/MoodBase.h"
#include "Thirst.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SIMULATION_API UThirst : public UMoodBase
{
	GENERATED_BODY()
public:
	virtual URGBehaviorTreeBase* GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent) ;

	
};
