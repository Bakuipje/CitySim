// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGCondition.generated.h"

/**
 * 
 */
class URGBehaviorTreeComponent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API URGCondition: public UObject
{
	GENERATED_UCLASS_BODY()

public:
	URGCondition();
	URGCondition(URGBehaviorTreeComponent* ownerComp);
	virtual ~URGCondition();
	UFUNCTION(BlueprintNativeEvent)
	bool Execute();
	
	URGBehaviorTreeComponent* m_ownerComp;

};
