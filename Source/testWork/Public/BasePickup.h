// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;
UCLASS()
class TESTWORK_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RespawnTime = 5.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void PickupWasTaken();
	void Respawn();
	virtual bool GivePickupTo(APawn* PlayerPawn);
};
