// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/GOAPBase.h"
#include "FindWater.generated.h"

/**
 * 
 */
class AStorageBase;
UCLASS()
class SIMULATION_API UFindWater : public UGOAPBase
{
	GENERATED_BODY()
public:
	UFindWater();
	~UFindWater();
	virtual void Reset();
	virtual bool IsDone();
	virtual bool CheckProceduralPrecondition(AAgent* agent);
	virtual bool Perform(AAgent* agent);
	virtual bool RequireInrange();
	
private:
	bool found = false;
	AStorageBase* waterStorage;
	
	
};
