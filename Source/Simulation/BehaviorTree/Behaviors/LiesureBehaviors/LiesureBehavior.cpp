// Fill out your copyright notice in the Description page of Project Settings.

#include "LiesureBehavior.h"
#include "MoodComponent.h"
#include "Moods/LiesureMood.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include "Building/House.h"
#include "Building/LiesureBase.h"
#include "EngineUtils.h"



void ULiesureBehavior::BeginPlay()
{
	liesureTimer = liesureDuration;
}

void ULiesureBehavior::Reset()
{
	URGBehaviorTreeBase::Reset();
	liesureTimer = liesureDuration;
}
EBehaviorState ULiesureBehavior::Tick_Implementation(float deltaTime)
{
	if (liesureTimer <= 0)
	{
		UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
		UMoodBase* currentMood = moodComp->GetMood(ULiesureMood::StaticClass());
		if (currentMood == nullptr)
			currentMood = moodComp->GetMood(ULiesureMood::StaticClass());
		m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
		moodComp->RemoveMood(currentMood->GetClass());
		AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
		owner->budget -= owner->liesurePlace->cost;
		owner->stress -= owner->liesurePlace->liesureAmount;
		owner->liesurePlace->AddRelationShips(owner, 1.0f, 0.1f);

		AddPrintString(FString("Finished relaxing, Gained" + FString::FromInt(owner->liesurePlace->liesureAmount) + " comfort and paid " + FString::FromInt(owner->liesurePlace->cost) + " units"));
		behaviorState = EBehaviorState::EB_Succeed;

		return behaviorState;
	}
	liesureTimer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}




