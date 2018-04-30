// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"
#include "RGAtLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API URGAtLocation:public URGCondition
{
	GENERATED_BODY()
public:
	URGAtLocation();
	URGAtLocation(URGBehaviorTreeComponent* ownerComp, FVector location, float radius);

	~URGAtLocation();
	virtual bool Execute_Implementation();
	FVector m_location;
	float m_radius;
};
