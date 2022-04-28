// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->InitSphereRadius(50.0f);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor) {

	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;
	if (GivePickupTo(Pawn)) {
        PickupWasTaken();
	}
	UE_LOG(LogBasePickup, Display, TEXT("Pickup"));

	

}
void ABasePickup::PickupWasTaken() {
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickup::Respawn, RespawnTime);
}
void ABasePickup::Respawn() {
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}
bool ABasePickup::GivePickupTo(APawn* PlayerPawn) {
	return false;
}
