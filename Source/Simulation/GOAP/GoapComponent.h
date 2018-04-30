// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Queue.h>
#include "GoapComponent.generated.h"

class UFiniteStateMachine;
class UFSMState;
class UGOAPBase;
class UGOAPPlanner;
class IGoapInterface;
class UIdleState;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATION_API UGoapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UIdleState* idleState;
	UFSMState* moveToState;
	UFSMState* performActionState;



	void CreateIdleState();
	void CreateMoveState();
	void CreatePerformAction();
	void FindDataProvider();
	void LoadActions();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void PostInit();
	void AddAction(UGOAPBase* action);
	UGOAPBase* GetAction(TSubclassOf<UGOAPBase> actionType);
	void RemoveAction(UGOAPBase* action);
	bool HasActionPlan();

	bool activate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UGOAPBase*> goapActions;
	IGoapInterface* dataProvider;
	UPROPERTY()
	UGOAPPlanner* planner;
	UPROPERTY()
	UFiniteStateMachine* stateMachine;
	UPROPERTY()
	TSet<UGOAPBase*> availableActions;
	TQueue<UGOAPBase*>* currentActions;

};
