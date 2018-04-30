// Fill out your copyright notice in the Description page of Project Settings.

#include "HasStorageBase.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

HasStorageBase::HasStorageBase()
{
}
HasStorageBase::HasStorageBase(URGBehaviorTreeComponent* ownerComp)
	:URGCondition(ownerComp)
{}

HasStorageBase::~HasStorageBase()
{
}
bool HasStorageBase::Execute()
{
	return ((AAgent*)(m_ownerComp->GetOwner()))->currentStorage != nullptr;
}
