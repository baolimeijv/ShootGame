#include "Components/HealthComponent.h"
#include"Engine/Engine.h"
#include"AbilitySystemInterface.h"
#include"GAS/MyAttributeSet.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	/*MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;*/
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	/*CurrentHealth = MaxHealth;*/
}

//void UHealthComponent::TakeDamage(float DamageAmount, AActor* DamageCauser)
//{
//	if (DamageAmount <= 0.0f || IsDead())
//	{
//		return;
//	}
//
//	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
//
//	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Damage:%f    CurrentHealth:%f"), DamageAmount,CurrentHealth));
//
//	if (IsDead())
//	{
//		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Dead")));
//
//		OnDeath.Broadcast();
//
//		AActor* OwnerActor = GetOwner();
//		if (OwnerActor)
//		{
//			OwnerActor->Destroy();
//		}
//	}
//}

//void UHealthComponent::Heal(float HealAmount)
//{
//	if (HealAmount <= 0.0f || IsDead())
//	{
//		return;
//	}
//
//	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
//}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
float UHealthComponent::GetCurrentHealth() const
{
	AActor* Owner = GetOwner();
	if (!Owner)return 0.f;

	IAbilitySystemInterface* GI = Cast<IAbilitySystemInterface>(Owner);
	if (!GI)return 0.f;

	UAbilitySystemComponent* ASC = GI->GetAbilitySystemComponent();
	if (!ASC)return 0.f;

	const UMyAttributeSet* AS = ASC->GetSet<UMyAttributeSet>();
	return AS ? AS->GetHealth() : 0.f;
}

float UHealthComponent::GetMaxHealth()const
{
	AActor *Owner = GetOwner();
	if (!Owner)return 0.f;

	IAbilitySystemInterface* GI = Cast<IAbilitySystemInterface>(Owner);
	if (!GI)return 0.f;

	UAbilitySystemComponent* ASC = GI->GetAbilitySystemComponent();
	if (!ASC)return 0.f;

	const UMyAttributeSet* AS = ASC->GetSet<UMyAttributeSet>();
	return AS ? AS->GetMaxHealth() : 0.f;
}
