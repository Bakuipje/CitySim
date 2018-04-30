// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RGBehaviorTreeComponent.generated.h"

class URGBehaviorTreeBase;
class URGBlackBoard;
class UMoodBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMULATION_API URGBehaviorTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's procurreperties
	URGBehaviorTreeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool dirty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviors)
		URGBehaviorTreeBase* rootNode = nullptr;
	UPROPERTY()
		URGBehaviorTreeBase* currentBehavior = nullptr;
	UPROPERTY()
		URGBehaviorTreeBase* tempBehavior = nullptr;
	URGBlackBoard* blackBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviors)
		TMap<TSubclassOf<UMoodBase>, URGBehaviorTreeBase*>m_moodBehaviors;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetCurrentBehavior(URGBehaviorTreeBase* behavior);
	URGBehaviorTreeBase* GetBehaviorTree();
	URGBlackBoard* GetBlackBoard();
	URGBehaviorTreeBase* GetRootNode();
	UFUNCTION(BlueprintCallable)
	void AddMoodBehavior(UMoodBase* mood);
	UFUNCTION(BlueprintCallable)
	void RemoveMoodBehavior(TSubclassOf<UMoodBase> moodType);
	void AbbortBehaviors();
};
