// Fill out your copyright notice in the Description page of Project Settings.

#include "MoodComponent.h"
#include "Moods/MoodBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include <Classes/GameFramework/Actor.h>
#include <UObject/UObjectGlobals.h>
#include "Moods/Hunger.h"
#include "Moods/Thirst.h"
// Sets default values for this component's properties
UMoodComponent::UMoodComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoodComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMoodComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	URGBehaviorTreeComponent* behaviorTreeComp = (URGBehaviorTreeComponent*)GetOwner()->GetComponentByClass(URGBehaviorTreeComponent::StaticClass());
	for (int i = 0; i < m_moods.Num(); i++)
	{
		behaviorTreeComp->AddMoodBehavior(m_moods[i]);
	}

}

void UMoodComponent::RemoveMood(TSubclassOf<UMoodBase> moodType)
{
	UMoodBase* removeMood = nullptr;
	
	for (int i = 0; i < m_moods.Num(); i++)
	{
		if (m_moods[i]->IsA(moodType))
			removeMood = m_moods[i];
	}
	if(removeMood!= nullptr)
		m_moods.Remove(removeMood);
}
UMoodBase* UMoodComponent::GetMood(TSubclassOf<UMoodBase> moodType)
{

	for (int i = 0; i < m_moods.Num(); i++)
	{
		if (m_moods[i]->IsA(moodType)||m_moods[i]->GetClass()->IsChildOf(moodType))
			return m_moods[i];
	}
	return nullptr;
}

void UMoodComponent::AddThinkingString(FString string)
{
	int counter = 0;
	int firstIndex = 0;
/*
	TArray<TCHAR> stringchar = thinkingString.GetCharArray();
	for (int i = 0; i < stringchar.Num(); i++)
	{
		if (stringchar[i] == '\n')
		{
			if (counter == 1)
				firstIndex = i;
			counter++;
		}
	}
	if (counter > maxLines)
		thinkingString.RemoveAt(0, firstIndex);*/
	thinkingString = string +FString("\n")+ thinkingString;
}

FString UMoodComponent::GetThinkingString()
{
	return thinkingString;
}