// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LineVisualizerButton.generated.h"

/**
 * 
 */
class AAgent;
UCLASS()
class SIMULATION_API ULineVisualizerButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	AAgent* ownerAgent;
	UPROPERTY(BlueprintReadWrite)
	AAgent* targetAgent;
	
	
	
};
