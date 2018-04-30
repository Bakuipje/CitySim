// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/GOAPBase.h"
#include "WaterPlant.generated.h"

/**
 * 
 */
class AStorageBase;
UCLASS()
class SIMULATION_API UWaterPlant : public UGOAPBase
{
	GENERATED_BODY()
public:
	UWaterPlant();
	~UWaterPlant();
	virtual void Reset();
	virtual bool IsDone();
	virtual bool CheckProceduralPrecondition(AAgent* agent);
	virtual bool Perform(AAgent* agent);
	virtual bool RequireInrange();

private:
	bool found = false;
	AStorageBase* plantStorage;
	
	
	
};
