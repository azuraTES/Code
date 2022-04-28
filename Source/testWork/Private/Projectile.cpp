// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(MovementComponent);
	check(CollisionComponent);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	SetLifeSpan(LifeSeconds);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, nullptr, {}, this, nullptr, DoFullDamage);
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	Destroy();
}

