// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "StationBehahavior.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API UStationBehahavior : public URGBehaviorTreeBase
{
	GENERATED_BODY()
	
public:
	virtual EBehaviorState Tick_Implementation(float deltaTime);
	class AStation* GetDestinationStation(AActor* m_destination);

	class AStation* destinationStation;
	class ATrain* train;
	
};
