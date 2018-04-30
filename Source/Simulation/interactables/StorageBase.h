// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "interactables/InteractableBase.h"
#include "StorageBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API AStorageBase : public AInteractableBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
		FVector m_standingLocation;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
		TArray<AInteractableBase*> m_interactables;
	bool HasInteractable(TSubclassOf<AInteractableBase> interactableType);
	AInteractableBase* GetInteractable(TSubclassOf<AInteractableBase> interactableType);
	void RemoveInteractable(TSubclassOf<AInteractableBase> interactableType);
	UFUNCTION(BlueprintCallable)
	FVector GetStandLocation();
	bool used = false;
	
	
};
