// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "WorkEnums.h"
#include "House.generated.h"

/**
 * 
 */


UCLASS()
class SIMULATION_API AHouse : public ABuildingBase
{
	GENERATED_BODY()

public:
	bool HasPlace(AAgent* agent);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int livingCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gainComfort;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EHouseType houseType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWorkType requiredWorkType;
	bool FixHousing(AAgent* self, AAgent* so);
	int currentfood;
	FString GetBuildingData_Implementation();
};
