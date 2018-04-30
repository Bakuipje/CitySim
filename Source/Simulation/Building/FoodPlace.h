// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "FoodPlace.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFoodType : uint8
{
	EF_FastFood UMETA(DisplayName = "fast food"),
	EF_NormalFood UMETA(DisplayName = "normal food"),
	EF_FancyFood UMETA(DisplayName = "fancy food")
};
class AAgent;
UCLASS()
class SIMULATION_API AFoodPlace : public ABuildingBase
{
	GENERATED_BODY()
public:
	bool HasPlace(AAgent* agent);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int foodAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int waitTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool allowHomeless;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFoodType foodType;

	FString GetBuildingData_Implementation();
	
};
