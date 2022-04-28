// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void ARifleWeapon::StartFire() {

	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
}
void ARifleWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

}
void ARifleWeapon::MakeShot() {
	if (!GetWorld() || IsAmmoEmpty()) {
		StopFire();
			return;
	};

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistans;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit) {
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);
		TakeDamage(HitResult);
		
	}
	DecreaseAmmo();
}

void ARifleWeapon::TakeDamage(const FHitResult& HitResult) {

	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}