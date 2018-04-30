// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGBehaviorTreeBase.generated.h"

/**
 *
 */
UENUM(BlueprintType)
 enum class EBehaviorState : uint8
{
	EB_Progress UMETA(DisplayName = "Progress"),
	EB_Succeed UMETA(DisplayName = "Succeed"),
	EB_Failed UMETA(DisplayName = "Failed")
};
class URGBehaviorTreeComponent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API URGBehaviorTreeBase: public UObject
{
	GENERATED_UCLASS_BODY()
public:
	URGBehaviorTreeBase(); 
//	URGBehaviorTreeBase(const FObjectInitializer& ObjectInitializer);
	URGBehaviorTreeBase(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost);
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay();
	UFUNCTION(BlueprintCallable)
		virtual void Init();
	UFUNCTION(BlueprintNativeEvent)
	 EBehaviorState Tick(float deltaTime);
	virtual void Reset();
	virtual ~URGBehaviorTreeBase();
	virtual URGBehaviorTreeBase* GetBehaviorTreeSegment(URGBehaviorTreeComponent* owner);
	virtual void AddPrintString(FString addString);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EBehaviorState behaviorState = EBehaviorState::EB_Progress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URGBehaviorTreeBase* m_parent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<URGBehaviorTreeBase*> m_behaviorList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URGBehaviorTreeComponent* m_ownerComp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	int m_cost = 0;

};
