// Fill out your copyright notice in the Description page of Project Settings.

#include "Node.h"
#include "GOAPBase.h"

Node::Node()
{
}

Node::~Node()
{
}
Node:: Node(Node* parent, float runningCost, TSet<TPair<EGoapIdentifier, bool>>* state, UGOAPBase* action)
{
	this->parent = parent;
	this->runningCost = runningCost;
	this->state = state;
	this->action = action;
}