// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "BaseWeapon.h"
#include "GameFramework/Character.h"

constexpr static int32 WeaponNum = 2;

UWeaponComponent::UWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}



void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	

	CurrentWeaponIndex = 0;
	
	//for character
	//SpawnWeapons();
	//EquipWeapon(CurrentWeaponIndex);
}
void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	CurrentWeapon = nullptr;
	//for (auto Weapon:Weapons) {
	//	Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//	Weapon->Destroy();
	//}
	//Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}
//for character
void UWeaponComponent::SpawnWeapons() {
	

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return;

	for (auto WeaponClass : WeaponClasses) {
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
		if (!Weapon) continue;
		Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}



	

	
	
}
//for character
void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
//for character
void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	if (CurrentWeapon) {
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}
void  UWeaponComponent::SetCurrentWeapon(ABaseWeapon* CurrentWeaponGrab) {
	CurrentWeapon =CurrentWeaponGrab;
}
void UWeaponComponent::StartFire(ABaseWeapon* CurrentWeaponGrab) {
	if (!CurrentWeaponGrab) return;
	CurrentWeaponGrab->StartFire();
}

void UWeaponComponent::StopFire(ABaseWeapon* CurrentWeaponGrab) {
	if (!CurrentWeaponGrab) return;
	CurrentWeaponGrab->StopFire();
}

void UWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
void UWeaponComponent::OnEmptyClip(ABaseWeapon* AmmoEmptyWeapon) {
	if (!AmmoEmptyWeapon) return;
	if (CurrentWeapon == AmmoEmptyWeapon) {
        ChangeClip(AmmoEmptyWeapon);
	}
	else {
		for (const auto Weapon : Weapons) {
			if (Weapon == AmmoEmptyWeapon) {
				Weapon->ChangeClip();
			}
		}
	}
	
}
void UWeaponComponent::ChangeClip(ABaseWeapon* AmmoEmptyWeapon) {
	AmmoEmptyWeapon->StopFire();
	AmmoEmptyWeapon->ChangeClip();
}
bool UWeaponComponent::TryAddToAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmount) {
	for (const auto Weapon : Weapons) {
		if (Weapon && Weapon->IsA(WeaponType)) {
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}