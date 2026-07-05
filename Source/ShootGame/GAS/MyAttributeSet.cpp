#include "GAS/MyAttributeSet.h"
#include"GameplayEffectExtension.h"
UMyAttributeSet::UMyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute()) 
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float finalHealth = GetHealth();
		if (finalHealth < 0.f)
		{

		}
	}
}
