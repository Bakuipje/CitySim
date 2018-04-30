// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoodBase.generated.h"
/**
 * 
 */
class URGBehaviorTreeBase;
class URGBehaviorTreeComponent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API UMoodBase: public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UMoodBase();
	virtual ~UMoodBase();
	UFUNCTION(BlueprintNativeEvent)
	URGBehaviorTreeBase* GetBehaviorTree(URGBehaviorTreeComponent* behviorTreeComponent);
	int severity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URGBehaviorTreeBase* behaviorTree;
    float statModifier;
};
