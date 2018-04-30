// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RelationComponent.generated.h"

class AAgent;
class AFoodPlace;
USTRUCT()
struct FRelationStruct
{
	GENERATED_BODY()

		UPROPERTY()
		float relationShip;
	UPROPERTY()
		AAgent* significantOther;
	FRelationStruct()
	{
		relationShip = 0.0f;
		significantOther = nullptr;
	}

};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMULATION_API URelationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URelationComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float friendlyValue= 2.0f;
	UPROPERTY()
		float hostileValue;
	UPROPERTY()
		AAgent* significatnOther;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool religious;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool athletic;
	// Called when the game starts
	void FillFoodMap();

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY()
	TMap<AAgent*, FRelationStruct> relationMap;
	UPROPERTY()
	TMap< int, int> foodMap;
	AAgent* GetSignificantOther();
	void AddRelationStats(AAgent* otheragent, float value);
	void AddSignificatnOther(AAgent* otherAgent);
	void CheckFoodmap();
	void GetFoodValue(int & fastValue, int& normalValue, int & fancyValue);
	UFUNCTION(BlueprintCallable)
		float GetFriendlyValue(AAgent* otherAgent);
	bool isReligious();
	bool isFriendly(AAgent* agent);
	bool isHostile(AAgent* agent);
	bool isAthletic();
};
