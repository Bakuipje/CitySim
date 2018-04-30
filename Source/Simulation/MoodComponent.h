// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoodComponent.generated.h"

class UMoodBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATION_API UMoodComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoodComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddThinkingString(FString string);
	UFUNCTION(BlueprintCallable)
		FString GetThinkingString();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moods)
	TArray<UMoodBase*> m_moods;
	void RemoveMood(TSubclassOf<UMoodBase> moodType);
	UMoodBase* GetMood(TSubclassOf<UMoodBase> moodType);
	float timer = 30;
	int maxLines = 10;

	FString thinkingString;
};
