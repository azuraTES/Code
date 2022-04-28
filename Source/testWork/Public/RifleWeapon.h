// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TESTWORK_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeBetweenShots = 0.10f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float DamageAmount = 10.0f;

private:
	FTimerHandle ShotTimerHandle;
	void TakeDamage(const FHitResult& HitResult);
	
};
