// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransportBase.generated.h"

class AAgent;
class AInteractionPoint;
UCLASS()
class SIMULATION_API ATransportBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransportBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitInteractionPoints();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveToLocation(FVector targetDestination);
	bool IsNear(FVector targetDestination, float range);

	TArray<AAgent*> visitors;
	TArray<AInteractionPoint*>interActionPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxVisitors;
	
	FVector m_destination;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed= 10;
	
};
