// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/Labourers/Labourers.h"
#include "GOAP/GOAPBase.h"
#include "Gardener.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API AGardener : public ALabourers
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	AGardener();
	virtual TSet<TPair<EGoapIdentifier, bool>> CreateGoalState();
	virtual void ActionsFinished();
	
};
