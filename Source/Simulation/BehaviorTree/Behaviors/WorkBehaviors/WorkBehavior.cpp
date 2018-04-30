// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkBehavior.h"
#include "MoodComponent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Moods/WorkMood.h"
#include "Agent.h"
#include "Building/OfficePLace.h"
#include "WorkEnums.h"
#include "GOAP/GoapComponent.h"
#include "EngineUtils.h"


void UWorkBehavior::BeginPlay()
{
	workTimer = workDuration;
}

void UWorkBehavior::Reset()
{
	URGBehaviorTreeBase::Reset();
	workTimer = workDuration;
}
void UWorkBehavior::Init()
{
	URGBehaviorTreeBase::Init();
	UGoapComponent* goap = (UGoapComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UGoapComponent::StaticClass());
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	workTimer = owner->workPlace->workTime;
	if (owner->workPlace->requiresGOAP)
		goap->PostInit();
}
EBehaviorState UWorkBehavior::Tick_Implementation(float deltaTime)
{
	UGoapComponent* goap = (UGoapComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UGoapComponent::StaticClass());
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();

	if (workTimer <= 0)
	{
		UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
		UMoodBase* currentMood = moodComp->GetMood(UWorkMood::StaticClass());
		if (currentMood == nullptr)
			currentMood = moodComp->GetMood(UWorkMood::StaticClass());
		m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
		moodComp->RemoveMood(currentMood->GetClass());
		owner->budget += owner->workPlace->compensation;

		owner->workExperienceMap[owner->workPlace->workType] += owner->workPlace->gainExperience;
		owner->stress += owner->workPlace->gainStress;
		AddPrintString(FString("Finished work " + owner->workPlace->GetName() + ", Gained " + FString::FromInt(owner->workPlace->compensation) + " units and " + FString::FromInt(owner->workPlace->gainExperience) + " experience"));
		owner->workPlace->AddRelationShips(owner, 1.0f, 0.5f);
		goap->activate = false;
		FindBetterWork(owner);
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	workTimer -= deltaTime;
	goap->activate = owner->workPlace->requiresGOAP;


	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}

void UWorkBehavior::FindBetterWork(AAgent* agent)
{
	float closestdist = 1e34;
	AOfficePlace* bestOfficePlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();

	int highestCompensation = agent->workPlace->compensation;
	if (world == nullptr)
	{
		return;
	}
	for (TActorIterator<AOfficePlace> officeItr(world); officeItr; ++officeItr)
	{
		AOfficePlace* officePlace = *officeItr;
		if (!officePlace->HasJob(ownerActor))
			continue;
		float dist = FVector::DistSquared2D(officePlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());
		if (officePlace->compensation >= highestCompensation)//dist < closestdist)
		{
			highestCompensation = officePlace->compensation;
			bestOfficePlace = officePlace;
			closestdist = dist;
		}
		if (officePlace->compensation >= highestCompensation&& dist < closestdist)//dist < closestdist)
		{
			highestCompensation = officePlace->compensation;
			bestOfficePlace = officePlace;
			closestdist = dist;
		}
	}

	if (bestOfficePlace == nullptr)
	{
		AddPrintString(FString("failed to find a better work"));
		return;
	}
	AddPrintString("found better work" + FString::FromInt(highestCompensation));
	agent->workPlace->RemoveVisitor(agent);
	agent->workPlace = bestOfficePlace;
	bestOfficePlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestOfficePlace, 0);// = bestOfficePlace;

}