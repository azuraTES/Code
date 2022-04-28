// Fill out your copyright notice in the Description page of Project Settings.


#include "StandartPickup.h"
#include "InventoryComponent.h"
bool AStandartPickup::GivePickupTo(APawn* PlayerPawn) {
	TArray<UActorComponent*> ActorComps;
	PlayerPawn->GetComponents<UActorComponent>(ActorComps);
	const auto InventoryComponent = PlayerPawn->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent) return false;

	return InventoryComponent->PickupItem(this);
}