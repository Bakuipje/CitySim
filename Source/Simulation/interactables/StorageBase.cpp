// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageBase.h"



FVector AStorageBase::GetStandLocation()
{
	return m_standingLocation + GetActorLocation();
}

bool AStorageBase::HasInteractable(TSubclassOf<AInteractableBase> interactableType)
{
	for (int i = 0; i < m_interactables.Num(); i++)
	{
		if (m_interactables[i]->IsA(interactableType))
			return true;
	}
	return false;
}
AInteractableBase* AStorageBase::GetInteractable(TSubclassOf<AInteractableBase> interactableType)
{
	for (int i = 0; i < m_interactables.Num(); i++)
	{
		if (m_interactables[i]->IsA(interactableType))
			return m_interactables[i];
	}
	return nullptr;
}

void AStorageBase::RemoveInteractable(TSubclassOf<AInteractableBase> interactableType)
{
	AInteractableBase* removeInteractable = nullptr;
	for (int i = 0; i < m_interactables.Num(); i++)
	{
		if (m_interactables[i]->IsA(interactableType))
		{
			removeInteractable = m_interactables[i];
			break;
		}
	}
	if (removeInteractable != nullptr)
	{
		removeInteractable->Destroy();
		m_interactables.Remove(removeInteractable);
	}
}