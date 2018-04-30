// Fill out your copyright notice in the Description page of Project Settings.

#include "TransportBase.h"
#include "Agent.h" 

// Sets default values
ATransportBase::ATransportBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATransportBase::BeginPlay()
{
	Super::BeginPlay();
	InitInteractionPoints();
	m_destination = GetActorLocation();
}

// Called every frame
void ATransportBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//if (!IsNear(m_destination, 100))
//	MoveToLocation(m_destination);

}

void ATransportBase::InitInteractionPoints()
{
	TArray<AActor*> children;
	GetAllChildActors(children);
	for (int i = 0; i < children.Num(); i++)
	{
		AInteractionPoint* interPoint = (AInteractionPoint*)children[i];
		if (interPoint!= nullptr)
			interActionPoints.Add(interPoint);
	}
}

void ATransportBase::MoveToLocation(FVector targetDestination)
{
	FVector dir = targetDestination - GetActorLocation();
	dir.Normalize();
	SetActorLocation(dir*moveSpeed + GetActorLocation());
}

bool ATransportBase::IsNear(FVector targetDestination, float range)
{
	FVector test = GetActorLocation();
	float value = FVector::DistSquared2D(targetDestination, GetActorLocation());
	return value < range*range;
}

