// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataVisualizerWidget.generated.h"

/**
 * 
 */
class AAgent;
class ABuildingBase;
UCLASS()
class SIMULATION_API UDataVisualizerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ClearMoodList();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ParsingData();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AddLineVisualizerButton(AAgent* ownerActor, const TArray<AAgent*>& targetActors);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ClearLineVisualizers();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABuildingBase* building;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEnabled;

	
};
