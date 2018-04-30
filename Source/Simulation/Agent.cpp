// Fill out your copyright notice in the Description page of Project Settings.

#include "Agent.h"
#include <DrawDebugHelpers.h>
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include <Navigation/PathFollowingComponent.h>
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "MoodComponent.h"
#include "RelationComponent.h"
#include "Moods/MoodBase.h"
#include "Building/House.h"
#include "Building/OfficePlace.h"
#include "Widgets/DataVisualizerWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Moods/AngryMood.h"
// Sets default values
AAgent::AAgent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitNames();
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	workExperienceMap.Add(EWorkType::WT_Office, 0);
	workExperienceMap.Add(EWorkType::WT_Farmer, 0);
	location = FVector(FMath::RandRange(0, 1000), FMath::RandRange(0, 1000), 0);
	behaviorTreeComp = (URGBehaviorTreeComponent*)GetComponentByClass(URGBehaviorTreeComponent::StaticClass());
	maxSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = maxSpeed / 2;
	agentName = GetAgentName();
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (stamina >= 0 && GetRelationComponent()->isAthletic())
		GetCharacterMovement()->MaxWalkSpeed = maxSpeed* exersice;
	else GetCharacterMovement()->MaxWalkSpeed = (maxSpeed*exersice) / 2;

	if (stress >= stressLimit)
		AddStressMood();
	if (hungerStat > 3)
	{
		GetMoodComponent()->AddThinkingString(FString("agent starved to death"));

		GetWorld()->SpawnActor<AActor>(grave, GetActorLocation(), GetActorRotation());
		Destroy();
	}
	//if(IsNear(location, GetActorLocation(),100))
	//	location = FVector(FMath::RandRange(0, 1000),  FMath::RandRange(0, 1000),0);
	//MoveTo( location);
	//DrawDebugSphere(GetWorld(),  location,10,10, FColor::Green);

}

void AAgent::MoveTo(FVector m_destination)
{
	UNavigationSystem* navSys = UNavigationSystem::GetCurrent(GetWorld());
	navSys->SimpleMoveToLocation(this->Controller, m_destination);

}

bool AAgent::IsNear(FVector loc1, FVector loc2, int range)
{
	int lengthsqr = FVector::DistSquared(loc1, loc2);
	if (range*range > lengthsqr)
		return true;
	return false;
}

void AAgent::AddWorkMood()
{
	if (stress < stressLimit)
	{
		UMoodComponent* moodComp = (UMoodComponent*)GetComponentByClass(UMoodComponent::StaticClass());
		moodComp->m_moods.Add(workmood);
	}
}

void AAgent::AddStressMood()
{
	UMoodComponent* moodComp = (UMoodComponent*)GetComponentByClass(UMoodComponent::StaticClass());
	UMoodBase* moodBase = moodComp->GetMood(stressMood->GetClass());
	if (!IsValid(moodBase))
		moodComp->m_moods.Add(stressMood);
}

void AAgent::PayBills()
{
	UMoodComponent* moodComp = (UMoodComponent*)GetComponentByClass(UMoodComponent::StaticClass());

	if (homePlace != nullptr)
	{
		if (budget - homePlace->livingCost > 0)
		{
			budget -= homePlace->livingCost / homePlace->AmountVisitor();
			moodComp->AddThinkingString(FString("paid house bills, paid ") + FString::FromInt(homePlace->livingCost));
		}
		else
		{
			moodComp->AddThinkingString(FString("Not Enough money to pay housing bills"));
			homePlace->RemoveVisitor(this);
			homePlace = nullptr;
		}
	}
}

void AAgent::GainComfort()
{
	UMoodComponent* moodComp = (UMoodComponent*)GetComponentByClass(UMoodComponent::StaticClass());
	if (homePlace != nullptr)
	{
		stress -= homePlace->gainComfort;
		stress = FMath::Max(0, stress);
	}
}

void AAgent::EatFood()
{
	if (homePlace != nullptr && homePlace->currentfood - 1 > 0)
		homePlace->currentfood = FMath::Max(0, homePlace->currentfood - 1);
	else GetMoodComponent()->m_moods.Add(foodMood);
}

void AAgent::AddGymMood()
{
	if (GetRelationComponent()->isAthletic())
	{
		GetMoodComponent()->m_moods.Add(gymMood);
	}
}

float AAgent::TimeToReachDestination(FVector m_destination, FVector Start = FVector())
{
	UNavigationSystem* navSys = UNavigationSystem::GetCurrent(GetWorld());
	float length = 0;
	if (Start == FVector())
		Start = GetActorLocation();
	navSys->GetPathLength(Start, m_destination, length);
	return length / GetCharacterMovement()->MaxWalkSpeed;
}
// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAgent::SetMaxdebugTextLines(int maxlines)
{
	GetMoodComponent()->maxLines = maxlines;
}

void AAgent::AttackAgent(AAgent* targetAgent)
{
	if (GetRelationComponent() == nullptr)
		return;
	if (!GetRelationComponent()->relationMap.Contains(targetAgent))
		return;
	if (GetRelationComponent()->relationMap[targetAgent].relationShip < -2)
	{
		UAngryMood* angrymood = NewObject<UAngryMood>();
		angrymood->SetTarget(targetAgent);
		GetMoodComponent()->m_moods.Add(angrymood);
		behaviorTreeComp->AbbortBehaviors();
		GetMoodComponent()->AddThinkingString(FString("Attacked " + targetAgent->agentName.ToString()));
	}
}

FString AAgent::GetActorStringStats()
{
	FString returnString;
	returnString = agentName.ToString() + ": Budget: " + FString::FromInt(budget) + " Stress: " + FString::FromInt(stress) + " office work experience" + FString::FromInt(workExperienceMap[EWorkType::WT_Office]) +
		" farmer experience" + FString::FromInt(workExperienceMap[EWorkType::WT_Farmer]) +
		" \n Athletic stat" + GetFloatAsStringWithPrecision(exersice, 3) + " hunger " + FString::FromInt(hungerStat);
	return returnString;
}

FString AAgent::GetAgentRelation(float relationValue, bool showString)
{
	if (!showString)return GetFloatAsStringWithPrecision(relationValue, 3);
	if (relationValue < -1.0f) return "hostile";
	if (relationValue < -0.5f)return "unfriendly";
	if (relationValue < 0.5f)return "neutral";
	if (relationValue < 2.0f)return "friendly";
	return "best friends";
}

FString AAgent::GetActorRelationStringStats(bool showString)
{
	FString returnString;
	URelationComponent* relComp = GetRelationComponent();
	TArray<AAgent*>agentList;
	for (auto& elem : relComp->relationMap)
	{
		if (IsValid(elem.Key))
		{
			if (elem.Value.relationShip != 0)
			{
				agentList.Add(elem.Key);
				URelationComponent* theirRelComp = elem.Key->GetRelationComponent();
				returnString += "relation with " + (elem.Key)->agentName.ToString() + " is " + GetAgentRelation(elem.Value.relationShip, showString) + " " +
					(elem.Key)->agentName.ToString() + " relation with you is " + GetAgentRelation(theirRelComp->relationMap[this].relationShip, showString) + "\n";
			}
		}
	}
	uiMood->AddLineVisualizerButton(this, agentList);

	return returnString;
}

URelationComponent* AAgent::GetRelationComponent()
{
	return (URelationComponent*)GetComponentByClass(URelationComponent::StaticClass());
}

UMoodComponent* AAgent::GetMoodComponent()
{
	return (UMoodComponent*)GetComponentByClass(UMoodComponent::StaticClass());
}

FName AAgent::GetAgentName()
{
	int index = FMath::RandRange(0, names.Num() - 1);
	return names[index];
}

EWorkType AAgent::GetWorkType()
{
	if (workPlace == nullptr)
		return EWorkType::WT_None;
	return workPlace->workType;
}
void AAgent::InitNames()
{
	names.Add("Dusty");
	names.Add("Buddy");
	names.Add("Galen");
	names.Add("Jerold");
	names.Add("Mervin");
	names.Add("Jermaine");
	names.Add("Kurt");
	names.Add("Jed");
	names.Add("Lyle");
	names.Add("Adam");
	names.Add("Hyman");
	names.Add("Wilford");
	names.Add("Jules");
	names.Add("Aubrey");
	names.Add("Len");
	names.Add("Kirby");
	names.Add("Greg");
	names.Add("Coleman");
	names.Add("Luis");
	names.Add("Willard");
	names.Add("Jeremy");
	names.Add("Malik");
	names.Add("Martin");
	names.Add("Willis");
	names.Add("Andres");
	names.Add("Nathanie");
	names.Add("Mario");
	names.Add("Cole");
	names.Add("Jorge");
	names.Add("Claudio");
	names.Add("Enrique");
	names.Add("Morton ");
	names.Add("Wilfred");
	names.Add("Jewel");
	names.Add("Sal");
	names.Add("Ruben");
	names.Add("Isaac");
	names.Add("Jerald ");
	names.Add("Zachariah");
	names.Add("Allen");
	names.Add("Kermit");
	names.Add("Chase");
	names.Add("Ben");
	names.Add("Mervin");
	names.Add("Alton");
	names.Add("Dominic");
	names.Add("Reggie");
	names.Add("Davis");
	names.Add("Buck");
	names.Add("Boyce");
	names.Add("Errol");
	names.Add("Kendall");
	names.Add("Rodney");
	names.Add("Kenny");
	names.Add("Jared");
	names.Add("Jeffry");
	names.Add("Jed");
	names.Add("Andy");
	names.Add("Ulysses");
	names.Add("Jamaal");
}

