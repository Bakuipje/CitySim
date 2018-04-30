// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"
#include "HasJob.generated.h"

/**
 *
 */
UCLASS()
class SIMULATION_API UHasJob : public URGCondition
{
	GENERATED_BODY()
public:

	virtual bool Execute_Implementation();



};
