// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"
#include "RGHasPath.generated.h"

/**
 * 
 */
class AAgent;
class UMoodBase;
UCLASS()
class SIMULATION_API URGHasPath : public URGCondition
{
	GENERATED_BODY()
	
public:
	virtual bool Execute_Implementation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector startLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector endLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAgent* agent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMoodBase* mood= nullptr;
	
};
