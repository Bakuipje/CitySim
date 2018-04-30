// Fill out your copyright notice in the Description page of Project Settings.

#include "InvertoryBase.h"


AInvertoryBase::AInvertoryBase()
{}
AInvertoryBase::~AInvertoryBase()
{}



int AInvertoryBase::GetMaxInventroy()
{
	return maxInventory;
}

void AInvertoryBase::SetMaxInvertory(int amount)
{
	maxInventory = amount;
}