// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherWeapon.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"

void ALauncherWeapon::StartFire() {
	MakeShot();
}

void ALauncherWeapon::MakeShot() {
    if (!GetWorld() || IsAmmoEmpty()) return;
	
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistans;
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile) {
		Projectile->SetShootDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);

	}
	DecreaseAmmo();
}