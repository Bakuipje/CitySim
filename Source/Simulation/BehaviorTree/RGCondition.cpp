// Fill out your copyright notice in the Description page of Project Settings.

#include "RGCondition.h"
#include "RGBehaviorTreeComponent.h"

URGCondition::URGCondition()
{}
URGCondition::URGCondition(FObjectInitializer const& ObjectInitializer)
{ }
URGCondition::URGCondition(URGBehaviorTreeComponent* ownerComp):m_ownerComp(ownerComp)
{
}

URGCondition::~URGCondition()
{
}

bool URGCondition::Execute_Implementation()
{
	return true;
}
