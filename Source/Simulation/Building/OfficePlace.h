// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "WorkEnums.h"
#include "OfficePlace.generated.h"
/**
 * 
 */
UCLASS()
class SIMULATION_API AOfficePlace : public ABuildingBase
{
	GENERATED_BODY()

public:
	bool HasJob(AAgent* agent);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int compensation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int neededExperience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gainExperience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gainStress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float workTime= 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		  EWorkType workType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool requiresGOAP;
	FString GetBuildingData_Implementation();

};
