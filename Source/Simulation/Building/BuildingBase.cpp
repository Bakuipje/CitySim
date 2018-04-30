// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingBase.h"
#include "World/InteractionPoint.h"
#include "Agent.h"
#include "EngineUtils.h"
#include "Widgets/DataVisualizerWidget.h"
#include "World/WorldRules.h"
#include "RelationComponent.h"
#include "MoodComponent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>

// Sets default values
ABuildingBase::ABuildingBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnClicked.AddDynamic(this, &ABuildingBase::DoActorCLicked);
}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	SearchInteractionPoints();

}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsValid(moodsWidget))
	{
		FindMoodswidget();
	}
	int removeid = -1;
	for (int i = 0; i < visitors.Num(); i++)
	{
		if (!IsValid(visitors[i]))
			removeid = i;
	}
	if (removeid >= 0)
		visitors.RemoveAt(removeid);
}

void ABuildingBase::AddVisitor(AAgent* agent)
{
	visitors.Add(agent);
}

void ABuildingBase::RemoveVisitor(AAgent* agent)
{
	visitors.Remove(agent);
	AInteractionPoint* intpoint = GetinteractionPoint(agent);
	if (intpoint != nullptr)
	{
		intpoint->occupied = false;
		intpoint->currentOwner = nullptr;
	}
}

void ABuildingBase::SetMaxVisitors(int owners)
{
	maxVisitors = owners;
}

void ABuildingBase::AddRelationShips(AAgent* agent, float positiveValue, float negativeValue)
{
	URelationComponent* relComp = (URelationComponent*)agent->GetComponentByClass(URelationComponent::StaticClass());
	for (int i = 0; i < visitors.Num(); i++)
	{
		if (!IsValid(visitors[i]))
		{
			visitors.RemoveAt(i);
			continue;
		}
		if (!IsValid(visitors[i]) || visitors[i] == agent)
			continue;
		float val = FMath::FRandRange(-negativeValue, positiveValue);
		relComp->AddRelationStats(visitors[i], val);
		agent->GetMoodComponent()->AddThinkingString(FString("relation with " + visitors[i]->agentName.ToString() +" gained relationpoints" + FString::SanitizeFloat(val)));
	}
}

void ABuildingBase::SearchInteractionPoints()
{
	TArray<AActor*>children;
	GetAllChildActors(children);
	for (int i = 0; i < children.Num(); i++)
	{
		AInteractionPoint* interactable = (AInteractionPoint*)children[i];
		if (IsValid(interactable))
			interactionPoints.Add(interactable);
	}
}

FVector ABuildingBase::GetDestination(AAgent* agent)
{
	FVector m_destination = GetActorLocation();
	AInteractionPoint* bestPoint = nullptr;
	for (int i = 0; i < interactionPoints.Num(); i++)
	{
		if (interactionPoints[i]->currentOwner == agent)
		{
			return interactionPoints[i]->GetActorLocation();
		}
		if (!interactionPoints[i]->occupied)
		{
			bestPoint = interactionPoints[i];
		}
	}
	if (bestPoint != nullptr)
	{
		m_destination = bestPoint->GetActorLocation();
		bestPoint->occupied = true;
		bestPoint->currentOwner = agent;
	}
	return m_destination;
}
void ABuildingBase::ClearInteraction()
{
	for (int i = 0; i < interactionPoints.Num(); i++)
	{
		interactionPoints[i]->currentOwner = nullptr;
		interactionPoints[i]->occupied = false;
	}
}

AInteractionPoint* ABuildingBase::GetinteractionPoint(AAgent* owner)
{
	for (int i = 0; i < interactionPoints.Num(); i++)
	{
		if (interactionPoints[i]->currentOwner == owner)
		{
			return interactionPoints[i];

		}
	}
	return nullptr;
}

FString ABuildingBase::GetBuildingData_Implementation()
{
	return "";
}

void ABuildingBase::DoActorCLicked(AActor* ClickedComp, FKey ButtonPressed)
{
	if (ButtonPressed.GetFName() == FName("LeftMouseButton"))
	{
		ClearActors();
		clicked = true;
		moodsWidget->ClearMoodList();
		moodsWidget->building = this;
		moodsWidget->ParsingData();
		EnableRoof(false);

	}
}

void ABuildingBase::ClearActors()
{
	for (TActorIterator<AAgent> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AAgent* agent = *ActorItr;
		agent->clicked = false;
		agent->EnableArrowVisual(false);
	}
	for (TActorIterator<ABuildingBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABuildingBase* buidling = *ActorItr;
		buidling->EnableRoof(true);
		buidling->clicked = false;
	}
}

void ABuildingBase::FindMoodswidget()
{
	for (TActorIterator<AWorldRules> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AWorldRules* world = *ActorItr;
		moodsWidget = world->dataVisualizerWidget;
	}
}

void ABuildingBase::EnableRoof_Implementation(bool enable)
{}

int ABuildingBase::AmountVisitor()
{
	return visitors.Num();
}
bool ABuildingBase::IsOpen()
{
	if (openTimes.Num() == 0)
		return true;
	UWorld* world = GetWorld();
	AWorldRules* worldRule = nullptr;
	for (TActorIterator<AWorldRules> stationItr(world); stationItr; ++stationItr)
	{
		worldRule = *stationItr;
	}
	ETimeState arrivalState = worldRule->TimeStateAtTime(0);
	for (int i = 0; i < openTimes.Num(); i++)
	{
		if (arrivalState == openTimes[i])
			return true;
	}
	return false;
}

bool ABuildingBase::IsOpenAtArrival(AAgent* agent)
{
	if(openTimes.Num() == 0)
	return true;
	UWorld* world = agent->GetWorld();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);
	UNavigationPath *tpath;
	tpath = NavSys->FindPathToLocationSynchronously(world, GetActorLocation(), agent->GetActorLocation());
	float dist = tpath->GetPathLength();
	float time =dist/ agent->maxSpeed;
	AWorldRules* worldRule = nullptr;
	for (TActorIterator<AWorldRules> stationItr(world); stationItr; ++stationItr)
	{
		worldRule = *stationItr;
	}
	ETimeState arrivalState = worldRule->TimeStateAtTime(time);
	for (int i = 0; i < openTimes.Num(); i++)
	{
		if (arrivalState == openTimes[i])
			return true;
	}
	return false;
}