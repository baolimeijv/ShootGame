#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent, BlueprintType))
class SHOOTGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	void TakeDamage(float DamageAmount, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	void Heal(float HealAmount);*/

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeathEvent OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return GetCurrentHealth() <= 0.f; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth()const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth()const;


protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
