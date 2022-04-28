// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);
bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn) {
	TArray<UActorComponent*> ActorComps;
	PlayerPawn->GetComponents<UActorComponent>(ActorComps);
	const auto HealthComponent = PlayerPawn->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = PlayerPawn->FindComponentByClass<UWeaponComponent>();
	if (!WeaponComponent) return false;

	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo Pickup"));
	return WeaponComponent->TryAddToAmmo(WeaponType, ClipsAmount);
}