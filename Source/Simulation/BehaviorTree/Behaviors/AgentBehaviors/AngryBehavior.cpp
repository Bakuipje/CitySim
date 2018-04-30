// Fill out your copyright notice in the Description page of Project Settings.

#include "AngryBehavior.h"
#include "MoodComponent.h"
#include "RelationComponent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Moods/AngryMood.h"
#include "Agent.h"


void UAngryBehavior::BeginPlay()
{
	argueTimer = argueTime;
}

void UAngryBehavior::Reset()
{
	URGBehaviorTreeBase::Reset();
	argueTimer = argueTime;
}

EBehaviorState UAngryBehavior::Tick_Implementation(float deltaTime)
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	if (argueTimer <= 0)
	{
		UMoodBase* currentMood = owner->GetMoodComponent()->GetMood(UAngryMood::StaticClass());
		if (currentMood == nullptr)
			currentMood = owner->GetMoodComponent()->GetMood(UAngryMood::StaticClass());
		m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
		owner->GetMoodComponent()->RemoveMood(currentMood->GetClass());

		owner->stress += stressAmount;

		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	owner->MoveTo(owner->GetActorLocation());
	owner->GetRelationComponent()->AddRelationStats(target,- 0.1);
	argueTimer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}
