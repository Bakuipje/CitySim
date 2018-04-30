// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "LiesureBase.generated.h"

/**
 * 
 */
class AAgent;
UCLASS()
class SIMULATION_API ALiesureBase : public ABuildingBase
{
	GENERATED_BODY()
	
public:
	bool HasPlace(AAgent* agent);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int liesureAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool religiousPlace;

	
	FString GetBuildingData_Implementation();

};
