// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPBase.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EGoapIdentifier : uint8
{
	GI_Water UMETA(DisplayName= "Has Water"),
	GI_Plants UMETA(DisplayName = "Has Plants"),
	GI_Key UMETA(DisplayName = "Has Key")
};
class AAgent;
UCLASS(Blueprintable, BlueprintType)
class SIMULATION_API UGOAPBase: public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UGOAPBase();
	~UGOAPBase();
	virtual void Reset();
	virtual bool IsDone();
	virtual bool CheckProceduralPrecondition(AAgent* agent);
	virtual bool Perform(AAgent* agent);
	virtual bool RequireInrange();
	bool IsinRange();
	void SetInRange(bool inrange);
	void AddPreconditions(EGoapIdentifier key, bool value);
	void removePreconditions(EGoapIdentifier key);
	void AddEffects(EGoapIdentifier key, bool value);
	void removeEffects(EGoapIdentifier key);
	TSet<TPair<EGoapIdentifier, bool>>* GetPreconditons();
	TSet<TPair<EGoapIdentifier, bool>>* GetEffects();
	UPROPERTY(EditAnywhere)
	float cost;
	AActor* target;
	TSet<TPair<EGoapIdentifier, bool>> *preconditions;
	TSet<TPair<EGoapIdentifier, bool>> *effects;
private:
	bool inRange;
};
