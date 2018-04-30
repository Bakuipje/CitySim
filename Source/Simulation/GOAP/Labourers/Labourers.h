// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "GOAP/GoapInterface.h"
#include "GOAP/GOAPBase.h"
#include "Labourers.generated.h"

/**
 * 
 */
class AInteractableBase;
class AInvertoryBase;
class AStorageBase;
UCLASS()
class SIMULATION_API ALabourers : public AAgent, public IGoapInterface
{
	GENERATED_BODY()
public:
	ALabourers();
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual TSet<TPair<EGoapIdentifier, bool>> GetWorldState();
	virtual TSet<TPair<EGoapIdentifier, bool>> CreateGoalState();
	virtual void PlanFailed(TSet<TPair<EGoapIdentifier, bool>> failedGoal);
	virtual void PlanFound(TSet<TPair<EGoapIdentifier, bool>> goal, TQueue<UGOAPBase*>* actions);
	virtual void ActionsFinished();
	virtual void PlanAborted(UGOAPBase* aborter) ;
	virtual bool MoveAgent(UGOAPBase* nextAction);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AInvertoryBase> waterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AInvertoryBase> KeyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AInteractableBase> waterstorageClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AInteractableBase> plantStorageClass;

	
	
	
};
