// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkEnums.h"
#include "BuildingBase.generated.h"

class AAgent;
class AInteractionPoint;
UCLASS()
class SIMULATION_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();
	int maxVisitors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	TArray<AAgent*> visitors;
	TArray<AInteractionPoint*> interactionPoints;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void DoActorCLicked(AActor* ClickedComp, FKey ButtonPressed);
	UFUNCTION(BlueprintCallable)
		void AddVisitor(AAgent* agent);
	UFUNCTION(BlueprintCallable)
		void RemoveVisitor(AAgent* agent);
	UFUNCTION(BlueprintCallable)
		void SetMaxVisitors(int owners);
	UFUNCTION(BlueprintCallable)
		bool IsOpenAtArrival(AAgent* agent);
	UFUNCTION(BlueprintCallable)
		bool IsOpen();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	 FString GetBuildingData();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EnableRoof(bool enable);
	void SearchInteractionPoints();
	FVector GetDestination(AAgent* agent);
	void ClearInteraction();
	void ClearActors();
	void FindMoodswidget();
	void AddRelationShips(AAgent* agent, float positiveValue, float negativeValue);
	int AmountVisitor();
	class AInteractionPoint* GetinteractionPoint(AAgent* owner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ETimeState> openTimes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool clicked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataVisualizerWidget* moodsWidget;

};
