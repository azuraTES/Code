// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTWORK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

    FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
    UFUNCTION(BlueprintCallable)
		bool IsDead() const { return Health <= 0.0; }
	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float MaxHealth = 100.0f;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
		bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
		float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
		float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
		float HealModifer = 5.0f;
	

public:	
	
		
private:
	float Health = 0.0f;

	UFUNCTION()
		void OnTakeAnyDamages(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle HealTimerHahdel;
	void HealUpdate();

	void SetHealth(float NewHealth);
	
};
