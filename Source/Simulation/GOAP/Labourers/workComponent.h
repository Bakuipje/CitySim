// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/GoapInterface.h"
#include "GOAP/GOAPBase.h"
#include "Components/ActorComponent.h"
#include "workComponent.generated.h"

class AInvertoryBase;
class AInteractableBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATION_API UworkComponent : public UActorComponent, public IGoapInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UworkComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual TSet<TPair<EGoapIdentifier, bool>> GetWorldState();
	virtual TSet<TPair<EGoapIdentifier, bool>> CreateGoalState();
	virtual void PlanFailed(TSet<TPair<EGoapIdentifier, bool>> failedGoal);
	virtual void PlanFound(TSet<TPair<EGoapIdentifier, bool>> goal, TQueue<UGOAPBase*>* actions);
	virtual void ActionsFinished();
	virtual void PlanAborted(UGOAPBase* aborter);
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
