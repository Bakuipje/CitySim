// Fill out your copyright notice in the Description page of Project Settings.

#include "RGBlackBoard.h"
//#include "BlackBoard/RGBlackBoardDataBase.h"




// Sets default values for this component's properties
URGBlackBoard::URGBlackBoard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URGBlackBoard::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URGBlackBoard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
/*
void URGBlackBoard::SetValue(FString name, RGBlackBoardDataBase* data)
{
	mapdata.Add(name, data);
}

RGBlackBoardDataBase* URGBlackBoard::Getdata(FString key)
{
	if(mapdata.Contains(key))
		return mapdata[key];
	return new RGBlackBoardDataBase();
}


bool URGBlackBoard::HasKey(FString key)
{
	return mapdata.Contains(key);
}

void URGBlackBoard::Erase(FString key)
{
	if (mapdata.Contains(key))
	{
		mapdata.Remove(key);
	}
}*/