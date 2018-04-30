// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPBase.h"
#include "Agent.h"
UGOAPBase::UGOAPBase()
{
	preconditions = new TSet<TPair<EGoapIdentifier, bool>>();
	effects = new TSet<TPair<EGoapIdentifier, bool>>();
}
UGOAPBase::UGOAPBase(FObjectInitializer const& ObjectInitializer)
{}

UGOAPBase::~UGOAPBase()
{
}

bool UGOAPBase::IsDone()
{
	return false;
}

bool UGOAPBase::CheckProceduralPrecondition(AAgent* agent)
{
	return false;
}

bool UGOAPBase::Perform(AAgent* agent)
{
	return false;
}
bool UGOAPBase::RequireInrange()
{
	return false;
}

void UGOAPBase::Reset()
{
	inRange = false;
	target = nullptr;
}

void UGOAPBase::SetInRange(bool inrange)
{
	inRange = inrange;
}

bool UGOAPBase::IsinRange()
{
	return inRange;
}

void UGOAPBase::removePreconditions(EGoapIdentifier key)
{
	TPair<EGoapIdentifier, bool >* remove = nullptr;
	TArray<TPair<EGoapIdentifier, bool>>pariArray = preconditions->Array();
	for (int i=0; i< pariArray.Num(); i++)
	{
	
		if (pariArray[i].Key == key)
			remove = &pariArray[i];
	}
	if (remove != nullptr)
		preconditions->Remove(*remove);

}

void UGOAPBase::AddPreconditions(EGoapIdentifier key, bool value)
{
	preconditions->Add(TPair<EGoapIdentifier, bool>(key, value));
}

void UGOAPBase::removeEffects(EGoapIdentifier key)
{
	TPair<EGoapIdentifier, bool >* remove = nullptr;
	TArray<TPair<EGoapIdentifier, bool>>pariArray = effects->Array();
	for (int i = 0; i < pariArray.Num(); i++)
	{

		if (pariArray[i].Key == key)
			remove = &pariArray[i];
	}
	if (remove != nullptr)
		effects->Remove(*remove);

}

void UGOAPBase::AddEffects(EGoapIdentifier key, bool value)
{
	effects->Add(TPair<EGoapIdentifier, bool>(key, value));
}