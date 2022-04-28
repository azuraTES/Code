// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"

// Sets default values for this component's properties
UDeathComponent::UDeathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDeathComponent::BeginPlay()
{
	Super::BeginPlay();
	ComponentOwner = GetOwner();
	TArray<UActorComponent*> ActorComps;
	ComponentOwner->GetComponents<UActorComponent>(ActorComps);
	HealthComponent = ComponentOwner->FindComponentByClass<UHealthComponent>();
	WeaponComponent = ComponentOwner->FindComponentByClass<UWeaponComponent>();
	HealthComponent->OnDeath.AddUObject(this, &UDeathComponent::OnDeath);
	
	
}




void UDeathComponent::OnDeath() {
	
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	UE_LOG(LogTemp, Warning, TEXT("dead"));
	ComponentOwner->SetLifeSpan(1.0f);
	
	if (GetWorld()) {
		
	}
	//WeaponComponent->StopFire();
}