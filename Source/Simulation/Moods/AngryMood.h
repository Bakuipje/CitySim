// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moods/MoodBase.h"
#include "AngryMood.generated.h"

/**
 *
 */
class AAgent;
UCLASS()
class SIMULATION_API UAngryMood : public UMoodBase
{
	GENERATED_BODY()
public:
	virtual URGBehaviorTreeBase* GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent);
	void SetTarget(AAgent* targetAgent);
	AAgent* target;


};
