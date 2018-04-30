// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "interactables/InteractableBase.h"
#include "InvertoryBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API AInvertoryBase : public AInteractableBase
{
	GENERATED_BODY()
protected:
	int maxInventory = 0;
public:
	AInvertoryBase();
	~AInvertoryBase();


	void SetMaxInvertory(int amount);
	int GetMaxInventroy();
};
