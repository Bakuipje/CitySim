// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transportation/TransportBase.h"
#include "Train.generated.h"

/**
 *
 */
class AStation;
class USplineComponent;
UCLASS()
class SIMULATION_API ATrain : public ATransportBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay()override;
public:

	virtual void Tick(float deltaTime)override;
	float GetTransportTime();
	void FindSpline();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float waitTime;
	float waitTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AStation* currentStation;
	AStation* nextStation;
	UPROPERTY()
		USplineComponent* followSpline;
	bool isMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int rideCost;
	float distance = 0.0f;
	//float time = 0;

};
