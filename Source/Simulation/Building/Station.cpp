// Fill out your copyright notice in the Description page of Project Settings.

#include "Station.h"
#include <Components/SplineComponent.h>
#include "Agent.h"

AStation::AStation()
{
	PrimaryActorTick.bCanEverTick = true;
	timer = 1.0f;
}

bool AStation::HasPLace(AAgent* agent)
{
	return agent->budget > cost;
}

void AStation::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (timer <= 0)
	{
		ClearInteraction();
		timer = 1.0f;
	}
	timer -= deltaTime;
}

AStation* AStation::GetNextStation()
{
	index++;
	if (index >= connectedStations.Num())
		index = 0;
	return connectedStations[index];
}

FVector AStation::GetTrainLocation()
{
	USplineComponent* followSpline = (USplineComponent*)GetComponentByClass(USplineComponent::StaticClass());

	return followSpline->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::World);
}

bool AStation::HasStation(TArray<AStation*> originalStations,AStation* targetStation)
{
	if (targetStation == this)
		return true;

	bool isLeft= false, isRight = false;
	originalStations.Add(this);
	if (connectedStations.Num() <= 0)
		return false;
	if (connectedStations.Num() > 0)
	{
		isLeft = targetStation == connectedStations[0];
		if (!isLeft)
		{
			if(originalStations.Contains(connectedStations[0]))
			isLeft=	connectedStations[0]->HasStation(originalStations,targetStation);

		}
		else return isLeft;
	}
	if (connectedStations.Num() > 1)
	{
		isLeft = targetStation == connectedStations[1];
		if (!isRight)
		{
			if (originalStations.Contains(connectedStations[1]))
				isRight =connectedStations[1]->HasStation(originalStations,targetStation);

		}
		else return isRight;
	}
	return isLeft||isRight;
}

FString AStation::GetBuildingData_Implementation()
{
	FString dataString = "";

	return dataString;
}
