// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"
#include "HasLiesurePlace.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UHasLiesurePlace : public URGCondition
{
	GENERATED_BODY()

public:
	bool Execute_Implementation();
	
	
};
