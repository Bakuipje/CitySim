// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "AthleticPlace.generated.h"

/**
 * 
 */
class AAgent;
UCLASS()
class SIMULATION_API AAthleticPlace : public ABuildingBase
{
	GENERATED_BODY()
public:
	bool HasPlace(AAgent* agent);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float exersiceGain = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float exersiceTime = 0.0f;
	
};
