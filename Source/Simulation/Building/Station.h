// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/BuildingBase.h"
#include "Station.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATION_API AStation : public ABuildingBase
{
	GENERATED_BODY()
	
public:
	AStation();
	virtual void Tick(float DeltaTime);
	bool HasPLace(AAgent* agent);
	bool HasStation(TArray<AStation*> originalStation,AStation* station);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AStation*> connectedStations;
	AStation* GetNextStation();
	class ATrain* currentTrain;
	FVector GetTrainLocation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector trainLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cost;
	float timer;
	int index;
	FString GetBuildingData_Implementation();


};
