#include "BaseCharacter/BaseCharacter.h"
#include"Components/HealthComponent.h"
#include"GAS/MyAttributeSet.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//创建ASC
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");

	Health = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	MyAttributeSet = NewObject<UMyAttributeSet>(this);
	if (AbilitySystemComponent)
	{
		//注入注册表
		AbilitySystemComponent->GetSpawnedAttributes_Mutable().Add(MyAttributeSet);
		AbilitySystemComponent->SetNumericAttributeBase(UMyAttributeSet::GetHealthAttribute(), MyAttributeSet->GetHealth());
		AbilitySystemComponent->SetNumericAttributeBase(UMyAttributeSet::GetMaxHealthAttribute(), MyAttributeSet->GetMaxHealth());
	}

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

