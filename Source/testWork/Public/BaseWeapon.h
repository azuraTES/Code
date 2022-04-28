// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ABaseWeapon*);

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};

UCLASS()
class TESTWORK_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	virtual void StartFire();
	virtual void StopFire();
	FOnClipEmptySignature OnClipEmpty;
	void ChangeClip();
	bool CanReload() const;
	bool TryToAddAmmo(int32 ClipsAmount);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FAmmoData DefaultAmmo{10, 15, false};

	virtual void MakeShot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";
	
	

	float TraceMaxDistans = 1500.0f;

	

	APlayerController* GetPlayerController() const;

	FVector GetMuzzleWorldLocation() const;

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	
	void LogAmmo();
	bool IsAmmoFull() const;

private:
	FAmmoData CurrentAmmo;

};
