// Fill out your copyright notice in the Description page of Project Settings.

#include "RGAtLocation.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/RGBlackBoard.h"
#include "Agent.h"

URGAtLocation::URGAtLocation()
{
}
URGAtLocation::URGAtLocation(URGBehaviorTreeComponent* ownerComp, FVector location, float radius) :
	URGCondition(ownerComp), m_location(location), m_radius(radius)
{}


URGAtLocation::~URGAtLocation()
{
}
bool URGAtLocation::Execute_Implementation()
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if (FVector::Distance(agent->GetActorLocation(), m_location) < m_radius)
		return true;
	return false;
}