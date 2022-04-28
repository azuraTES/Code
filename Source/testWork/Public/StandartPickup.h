// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "StandartPickup.generated.h"

/**
 * 
 */
UCLASS()
class TESTWORK_API AStandartPickup : public ABasePickup
{
	GENERATED_BODY()
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
