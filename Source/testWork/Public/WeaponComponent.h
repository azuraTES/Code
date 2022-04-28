// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTWORK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UWeaponComponent();
	UFUNCTION(BlueprintCallable)
	    void StartFire(ABaseWeapon* CurrentWeaponGrab);
	UFUNCTION(BlueprintCallable)
		void StopFire(ABaseWeapon* CurrentWeaponGrab);
	UFUNCTION(BlueprintCallable)
		void NextWeapon();
	
	bool TryAddToAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmount);
protected:
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		void SetCurrentWeapon(ABaseWeapon* CurrentWeaponGrab);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	    FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName = "ArmorySocket";
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:	
	void SpawnWeapons();
	
	UPROPERTY()
	    ABaseWeapon* CurrentWeapon;

	//UPROPERTY()
		TArray<ABaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void OnEmptyClip(ABaseWeapon* AmmoEmptyWeapon);
	void ChangeClip(ABaseWeapon* AmmoEmptyWeapon);
};
