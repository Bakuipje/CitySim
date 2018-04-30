// Fill out your copyright notice in the Description page of Project Settings.

#include "FailedFood.h"
#include "MoodComponent.h"
#include "Moods/FoodMood.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"

EBehaviorState UFailedFood::Tick_Implementation(float deltaTime)
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	owner->stress += stressAmount;
	owner->hungerStat++;
	UMoodComponent* moodComp = owner->GetMoodComponent();
	UMoodBase* currentMood = moodComp->GetMood(UFoodMood::StaticClass());
	m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
	moodComp->RemoveMood(currentMood->GetClass());
	AddPrintString(FString("no place to eat gained " + FString::FromInt(stressAmount) + "stress"));
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}


