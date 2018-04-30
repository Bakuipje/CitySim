// Fill out your copyright notice in the Description page of Project Settings.

#include "AthleticPlace.h"
#include "Agent.h"

bool AAthleticPlace::HasPlace(AAgent* agent)
{
	return agent->budget>cost;
}

