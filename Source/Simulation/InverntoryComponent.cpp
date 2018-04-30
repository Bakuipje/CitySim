// Fill out your copyright notice in the Description page of Project Settings.

#include "InverntoryComponent.h"
#include "interactables/InvertoryBase.h"
// Sets default values for this component's properties
UInverntoryComponent::UInverntoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInverntoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInverntoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UInverntoryComponent::GetInventory(AInvertoryBase* inventory)
{
	if (m_inventory.Contains(inventory->GetClass()))
		return m_inventory[inventory->GetClass()];
	else return 0;
}

int UInverntoryComponent::GetInventory(TSubclassOf<AInvertoryBase> inventoryType)
{
	if (m_inventory.Num() <= 0)
		return 0;
	for  (auto invetory : m_inventory)
	{
		if (invetory.Key->IsChildOf(inventoryType))
			return invetory.Value;

	}
	 return 0;
}

int UInverntoryComponent::AddInventroy(AInvertoryBase* inventory, int amount)
{
	int returnValue = 0;
	if (m_inventory.Contains(inventory->GetClass()))
	{
		if(m_inventory[inventory->GetClass()]+ amount< inventory->GetMaxInventroy())
		m_inventory[inventory->GetClass()] += amount;
		else 
		{
			returnValue = amount + m_inventory[inventory->GetClass()] - inventory->GetMaxInventroy();
			m_inventory[inventory->GetClass()] = inventory->GetMaxInventroy();
		}
	}
	else 
	{
		m_inventory.Add(inventory->GetClass(), amount);
		returnValue = amount - inventory->GetMaxInventroy();
		if (returnValue <= 0) returnValue = 0;
	}
		return returnValue;
}

int UInverntoryComponent::RemoveInventory(AInvertoryBase* inventory, int amount)
{
	int returnValue = 0;
	if (m_inventory.Contains(inventory->GetClass()))
	{
		m_inventory[inventory->GetClass()] -= amount;
		if (m_inventory[inventory->GetClass()] <= 0)
		{
			returnValue = m_inventory[inventory->GetClass()];
			FMath::Abs(returnValue);
			m_inventory.Remove(inventory->GetClass());
		}
	}
	return returnValue;
}

int UInverntoryComponent::RemoveInventory(TSubclassOf<AInvertoryBase> invetoryType, int amount)
{
	int returnValue = 0;
	TSubclassOf<AInvertoryBase> removeInventory = nullptr;
	for (auto invetory : m_inventory)
	{
		if (invetory.Key->IsChildOf(invetoryType))
		{
			invetory.Value -= amount;
			if (invetory.Value <= 0)
			{
				returnValue = invetory.Value;
				FMath::Abs(returnValue);
				removeInventory = invetory.Key;
			}
		}
	}
	if (removeInventory!= nullptr)
	{
		m_inventory.Remove(removeInventory);
	}
	return returnValue;
}