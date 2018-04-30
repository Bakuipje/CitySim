// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moods/MoodBase.h"
#include "FoodMood.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UFoodMood : public UMoodBase
{
	GENERATED_BODY()
public:
		virtual URGBehaviorTreeBase* GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent);

	
};