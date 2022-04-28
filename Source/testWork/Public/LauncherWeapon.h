// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class AProjectile;

UCLASS()
class TESTWORK_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	virtual void MakeShot() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AProjectile> ProjectileClass;
	
};
