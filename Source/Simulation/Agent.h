// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WorkEnums.h"
#include "Agent.generated.h"

class AStorageBase;
class AOfficePlace;
class UMoodBase;
class AHouse;
class ALiesureBase;
class AFoodPlace;
class AAthleticPlace;
class URelationComponent;
class UMoodComponent;


UCLASS()
class SIMULATION_API AAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void MoveTo(FVector m_destination);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddWorkMood();
	void AddStressMood();
	void AddGymMood();
	void PayBills();
	void GainComfort();
	void EatFood();
	void InitNames();

	bool IsNear(FVector loc1, FVector loc2, int range);
	float TimeToReachDestination(FVector m_destination, FVector Start);
	FString GetAgentRelation(float relationValue,bool showString);
	FName GetAgentName();
	URelationComponent* GetRelationComponent();
	UMoodComponent* GetMoodComponent();
	EWorkType GetWorkType();
	
	static FORCEINLINE FString GetFloatAsStringWithPrecision(float TheFloat, int32 Precision, bool IncludeLeadingZero = true)
	{
		//Round to integral if have something like 1.9999 within precision
		float Rounded = roundf(TheFloat);
		if (FMath::Abs(TheFloat - Rounded) < FMath::Pow(10, -1 * Precision))
		{
			TheFloat = Rounded;
		}
		FNumberFormattingOptions NumberFormat;					//Text.h
		NumberFormat.MinimumIntegralDigits = (IncludeLeadingZero) ? 1 : 0;
		NumberFormat.MaximumIntegralDigits = 10000;
		NumberFormat.MinimumFractionalDigits = 1;
		NumberFormat.MaximumFractionalDigits = Precision;
		return FText::AsNumber(TheFloat, &NumberFormat).ToString();
	}

	UFUNCTION(BlueprintCallable)
		FString GetActorStringStats();
	UFUNCTION(BlueprintCallable)
		FString GetActorRelationStringStats(bool showString);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void EnableArrowVisual(bool enable);
	UFUNCTION(BlueprintCallable)
		void SetMaxdebugTextLines(int maxlines);
	UFUNCTION(BlueprintCallable)
		void AttackAgent(AAgent* targetAgent);

	FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AStorageBase* currentStorage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> moveLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AOfficePlace* workPlace = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHouse* homePlace = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ALiesureBase* liesurePlace = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AFoodPlace* foodPlace = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AStation* stationPlace = nullptr;
	UPROPERTY()
		AAthleticPlace* gym = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMoodBase* workmood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMoodBase* stressMood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMoodBase* foodMood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMoodBase* gymMood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataVisualizerWidget* uiMood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf< AActor> grave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int budget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int stressLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool clicked;
	UPROPERTY(EditAnywhere, BlueprintReadOnly )
		FName agentName;
	int stress;
	int hungerStat =0;
	TMap<EWorkType, int> workExperienceMap;
	float exersice = 1.0;
	float stamina = 10.0f;
	float maxSpeed;
	class URGBehaviorTreeComponent* behaviorTreeComp = nullptr;
	 TArray<FName> names;
	
};
