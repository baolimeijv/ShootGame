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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.0f;

	UPROPERTY(BlueprintAssignable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FOnDeathEvent OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	void TakeDamage(float DamageAmount, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool IsDead() const { return CurrentHealth <= 0.0f; }

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
