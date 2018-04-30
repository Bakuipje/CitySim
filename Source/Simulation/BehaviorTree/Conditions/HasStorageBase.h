// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/RGCondition.h"

/**
 * 
 */
class SIMULATION_API HasStorageBase:public URGCondition
{
public:
	HasStorageBase();
	~HasStorageBase();
	HasStorageBase(URGBehaviorTreeComponent* ownerComp);
	virtual bool Execute();

};
