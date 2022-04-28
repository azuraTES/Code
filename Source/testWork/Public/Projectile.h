// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TESTWORK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();
	void SetShootDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		USphereComponent* CollisionComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		UProjectileMovementComponent* MovementComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		float DamageRadius = 200.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		float DamageAmount = 50.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "FullDamage")
		bool DoFullDamage = true;
	UPROPERTY(VisibleDefaultsOnly, Category = "LifeProjectile")
		float LifeSeconds = 5.0f;
	virtual void BeginPlay() override;

private:	
	FVector ShotDirection;
	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
