// Fill out your copyright notice in the Description page of Project Settings.

#include "RGHasPath.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Simulation/Agent.h"
#include "interactables/StorageBase.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include <Navigation/PathFollowingComponent.h>
#include "MoodComponent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

bool URGHasPath::Execute_Implementation()
{
	UNavigationSystem* navSys = UNavigationSystem::GetCurrent(agent->GetWorld());

	FPathFindingQuery pathQueary;
	pathQueary.StartLocation = agent->GetActorLocation();
	pathQueary.EndLocation = agent->currentStorage->GetStandLocation();
	pathQueary.NavData = navSys->GetMainNavData();
	pathQueary.Owner = m_ownerComp->GetOwner();
	pathQueary.SetAllowPartialPaths(false);
	bool returnvalue = navSys->TestPathSync(pathQueary, EPathFindingMode::Hierarchical);
	if (!returnvalue&& mood!= nullptr)
	{
		UMoodComponent* moodcomp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
		moodcomp->m_moods.Add(mood);
	}
	return returnvalue;
}
