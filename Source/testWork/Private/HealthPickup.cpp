// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "HealthComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);
bool AHealthPickup::GivePickupTo(APawn* PlayerPawn) {
	TArray<UActorComponent*> ActorComps;
	check(PlayerPawn);
	PlayerPawn->GetComponents<UActorComponent>(ActorComps);
	const auto HealthComponent = PlayerPawn->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmmount);
}