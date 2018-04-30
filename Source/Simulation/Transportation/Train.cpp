// Fill out your copyright notice in the Description page of Project Settings.

#include "Train.h"
#include <Components/SplineComponent.h>
#include "Building/Station.h"

void ATrain::BeginPlay()
{
	Super::BeginPlay();
	waitTimer = waitTime;
	m_destination = currentStation->GetTrainLocation();
	nextStation = currentStation->GetNextStation();
	isMoving = true;
	FindSpline();
}

void ATrain::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
//	USplineComponent* spline = (USplineComponent*)currentStation->GetComponentByClass(USplineComponent::StaticClass());
	float speed = moveSpeed;// / spline->GetSplineLength();
	distance += speed;
	SetActorLocation(followSpline->GetLocationAtDistanceAlongSpline(distance,ESplineCoordinateSpace::World));
	SetActorRotation(followSpline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World));
	if (IsNear(nextStation->GetTrainLocation(), 300))
	{
		nextStation->currentTrain = this;
		if (waitTimer <= 0)
		{
			nextStation->currentTrain = nullptr;
			currentStation = nextStation;
			nextStation = currentStation->GetNextStation();
			FindSpline();
			waitTimer = waitTime;
			isMoving = true;
		}
		waitTimer -= deltaTime;
		isMoving = false;
	}
}

float ATrain::GetTransportTime()
{
	float length = FVector::Dist(currentStation->GetTrainLocation(), nextStation->GetTrainLocation());
	return length/ moveSpeed;
}

void ATrain::FindSpline()
{
	followSpline = (USplineComponent*)currentStation->GetComponentByClass(USplineComponent::StaticClass());
	float dist = FVector::Dist(followSpline->GetLocationAtTime(1.0f, ESplineCoordinateSpace::World), nextStation->GetTrainLocation());
	if ( dist> 300)
	{
		followSpline = (USplineComponent*)nextStation->GetComponentByClass(USplineComponent::StaticClass());
		moveSpeed = -FMath::Abs(moveSpeed);
		distance = followSpline->GetSplineLength();
	}
	else
	{
		moveSpeed = FMath::Abs(moveSpeed);
		distance = 0;
	}
}