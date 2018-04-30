// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldRules.h"
#include <Components/DirectionalLightComponent.h>
#include "Simulation/Agent.h"
#include "Building/BuildingBase.h"
#include "EngineUtils.h"


// Sets default values
AWorldRules::AWorldRules()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	worldTimeState = ETimeState::TS_Morning;

}

// Called when the game starts or when spawned
void AWorldRules::BeginPlay()
{
	Super::BeginPlay();
	segmentTimer = segmentTime;
	skyColor = GetTimeCollor(ETimeState::TS_Morning);
	CorrectBuildingPlacement(-130);
}

// Called every frame
void AWorldRules::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (segmentTimer < 0)
	{
		worldTimeState=	ChangeTime(worldTimeState);
		segmentTimer = segmentTime;
	}
	segmentTimer -= DeltaTime;

	skyColor = GetTimeCollor(worldTimeState);//FMath::Lerp(GetTimeCollor(worldTimeState), GetTimeCollor(ChangeTime(worldTimeState)), segmentTime - segmentTimer);
	ApplySkyColor();
}

void AWorldRules::CorrectBuildingPlacement(float height)
{
	for (TActorIterator<ABuildingBase> buildingItr(GetWorld()); buildingItr; ++buildingItr)
	{
		ABuildingBase* building = *buildingItr;
		FVector actorLoc = building->GetActorLocation();
		building->SetActorLocation(FVector(actorLoc.X, actorLoc.Y, height));
	}
}

ETimeState AWorldRules::ChangeTime(ETimeState timeState)
{
	switch (timeState)
	{
	case ETimeState::TS_Morning:
		return ETimeState::TS_Afternoon;
	case ETimeState::TS_Afternoon:
		return ETimeState::TS_Evening;
	case ETimeState::TS_Evening:
	{
		AgentApplyStats();
		return ETimeState::TS_Night;
	}
	case ETimeState::TS_Night:
	{
		AddMoodAgents();
		return ETimeState::TS_Morning;
	}
	default:
		return ETimeState::TS_Morning;
	}
}

ETimeState AWorldRules::TimeStateAtTime(float time)
{
	int segmentAmount = time / segmentTime;
	int timeState = (int)worldTimeState + segmentAmount;
	timeState %= 4;
	return (ETimeState)timeState;
}

void AWorldRules::AddMoodAgents()
{
	for (TActorIterator<AAgent> agentItr(GetWorld()); agentItr; ++agentItr)
	{
		AAgent* agent = *agentItr;
		agent->AddWorkMood();
		agent->AddGymMood();

	}
}

void AWorldRules::AgentApplyStats()
{
	for (TActorIterator<AAgent> agentItr(GetWorld()); agentItr; ++agentItr)
	{
		AAgent* agent = *agentItr;
		agent->PayBills();
		agent->GainComfort();
		agent->EatFood();
	}
}


void AWorldRules::ApplySkyColor()
{
	UDirectionalLightComponent* light = Cast<UDirectionalLightComponent>(lights->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
	light->SetLightColor(skyColor);
}

FLinearColor AWorldRules::GetTimeCollor(ETimeState timeState)
{
	switch (timeState)
	{
	case ETimeState::TS_Morning:
		return morningColor;
	case ETimeState::TS_Afternoon:
		return afternoonColor;
	case ETimeState::TS_Evening:
		return eveningColor;
	case ETimeState::TS_Night:
		return nightColor;
	default:
		return morningColor;
	}
}


