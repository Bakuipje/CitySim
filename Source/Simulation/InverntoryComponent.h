// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InverntoryComponent.generated.h"

class AInvertoryBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATION_API UInverntoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInverntoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TMap<TSubclassOf<AInvertoryBase>, int> m_inventory;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
 
	int AddInventroy(AInvertoryBase* inventory, int amount);
	int RemoveInventory(AInvertoryBase* inventory, int amount);
	UFUNCTION(BlueprintCallable)
	int RemoveInventory(TSubclassOf<AInvertoryBase> invetoryType, int amount);
	int GetInventory(AInvertoryBase* inventory);
	UFUNCTION(BlueprintCallable)
	int GetInventory(TSubclassOf<AInvertoryBase> invetoryType);
	
};
