// Fill out your copyright notice in the Description page of Project Settings.

#include "GymBehavior.h"
#include "MoodComponent.h"
#include "RelationComponent.h"
#include "Moods/GymMood.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

#include "Building/AthleticPlace.h"
#include "Agent.h"

void UGymBehavior::Init()
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	gymTimer = owner->gym->exersiceGain;
}

EBehaviorState UGymBehavior::Tick_Implementation(float deltaTime)
{
	if (gymTimer <= 0)
	{
		AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
		UMoodComponent* moodcomp = owner->GetMoodComponent();
		UMoodBase* currentMood = moodcomp->GetMood(UGymMood::StaticClass());
		m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
		moodcomp->RemoveMood(currentMood->GetClass());
		owner->gym->AddRelationShips(owner, 0.3f, 0.3f);
		owner->budget -= owner->gym->cost;
		owner->exersice += owner->gym->exersiceGain;
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}

	gymTimer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;

}

