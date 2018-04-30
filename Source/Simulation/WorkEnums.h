// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkEnums.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EWorkType : uint8
{
	WT_Office UMETA(DisplayName = "office worker"),
	WT_Farmer UMETA(DisplayName = "farmer"),
	WT_None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EHouseType : uint8
{
	EH_HomelessHouse UMETA(DisplayName = "homeless house"),
	EH_NormalHouse UMETA(DisplayName = "normal house"),
	EH_FancyHouse UMETA(DisplayName = "fancy house")
};

UENUM(BlueprintType)
enum class ETimeState : uint8
{
	TS_Morning UMETA(DisplayName = "Morning"),
	TS_Afternoon UMETA(DisplayName = "Afternoon"),
	TS_Evening UMETA(DisplayName = "Evening"),
	TS_Night UMETA(DisplayName = "Night")
};
UCLASS()
class SIMULATION_API AWorkEnums : public AActor
{
	GENERATED_BODY()

public:
	AWorkEnums();
	~AWorkEnums();
};
