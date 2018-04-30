// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorAIController.h"
#include <Navigation/CrowdFollowingComponent.h>




ASimulatorAIController::ASimulatorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}