// Fill out your copyright notice in the Description page of Project Settings.

#include "MoodBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

UMoodBase::UMoodBase()
{
}
UMoodBase::UMoodBase(FObjectInitializer const& objectInitializer)
{}

UMoodBase::~UMoodBase()
{
}

URGBehaviorTreeBase* UMoodBase::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	return nullptr;
}