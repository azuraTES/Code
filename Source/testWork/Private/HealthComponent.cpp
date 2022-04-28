// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner) {
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamages);
		
	}
	
}


void UHealthComponent::OnTakeAnyDamages(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	SetHealth(Health - Damage);
	
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHahdel);
	if (IsDead()) {
		OnDeath.Broadcast();
	}
	else if (AutoHeal) {
		GetWorld()->GetTimerManager().SetTimer(HealTimerHahdel, this, &UHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
}

void UHealthComponent::HealUpdate(){
	SetHealth(Health + HealModifer);
	

	if (IsHealthFull() && GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHahdel);
	}
}




void UHealthComponent::SetHealth(float NewHealth) {
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
bool UHealthComponent::TryToAddHealth(float HealthAmount) {
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealthAmount);
	return true;
}
bool UHealthComponent::IsHealthFull() const {
	return FMath::IsNearlyEqual(Health, MaxHealth);
}