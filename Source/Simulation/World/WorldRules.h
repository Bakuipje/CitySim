// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkEnums.h"
#include "WorldRules.generated.h"


UCLASS()
class SIMULATION_API AWorldRules : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldRules();
	FLinearColor skyColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FLinearColor GetTimeCollor(ETimeState timestate);
	void ApplySkyColor();
	void AgentApplyStats();
	void AddMoodAgents();
	void CorrectBuildingPlacement(float height);

	ETimeState ChangeTime(ETimeState timeState);
	UFUNCTION(BlueprintCallable)
		ETimeState TimeStateAtTime(float time);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float segmentTime;
	float segmentTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		ETimeState worldTimeState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataVisualizerWidget* dataVisualizerWidget;
	UPROPERTY(EditAnywhere)
		AActor* lights;
	UPROPERTY(EditAnywhere)
		FLinearColor morningColor;
	UPROPERTY(EditAnywhere)
		FLinearColor afternoonColor;
	UPROPERTY(EditAnywhere)
		FLinearColor eveningColor;
	UPROPERTY(EditAnywhere)
		FLinearColor nightColor;
	UPROPERTY(EditAnywhere)
		float buildingHeight;
};
