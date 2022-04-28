// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "StandartPickup.h"
#define MAX_INVENTORY_ITEMS 5
DEFINE_LOG_CATEGORY_STATIC(LogInventoryComponent, All, All)

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory.SetNum(MAX_INVENTORY_ITEMS);
	ItemTouch = nullptr;
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::PickupItem(AStandartPickup* LastItemTouch) {
	
		//Find the first available slot
		int32 AvailableSlot = Inventory.Find(nullptr);

		if (AvailableSlot != INDEX_NONE)
		{
			//Add the item to the first valid slot we found
			Inventory[AvailableSlot] = LastItemTouch;
			//Destroy the item from the game
			LastItemTouch->Destroy();
			UE_LOG(LogInventoryComponent, Display, TEXT("LastItemTouch"));
			return true;
			GLog->Log("You can't carry any more items!");
		}
		else return false;
	
}
