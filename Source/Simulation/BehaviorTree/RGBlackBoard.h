// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RGBlackBoard.generated.h"

class RGBlackBoardDataBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMULATION_API URGBlackBoard : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URGBlackBoard();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TMap<FString, RGBlackBoardDataBase*> mapdata;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//void SetValue(FString name, RGBlackBoardDataBase* data);
	//RGBlackBoardDataBase* Getdata(FString key);
	// bool HasKey(FString key);
	// void Erase(FString key);

};
