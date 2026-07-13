#include "GAS/MyGASHelper.h"
#include"GameplayEffect.h"
#include"AbilitySystemComponent.h"
#include"AbilitySystemInterface.h"


void UMyGASHelper::ApplyDamage(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC, float DamageCount, TSubclassOf<UGameplayEffect> DamageEffectClass)
{
	if (!SourceASC || !TargetASC || !DamageEffectClass)return;
	if (DamageCount < 0.f)return;

	//绑定发出者生成上下文
	FGameplayEffectContextHandle Context = SourceASC->MakeEffectContext();
	Context.AddSourceObject(SourceASC->GetOwnerActor());

	//效果数据包
	FGameplayEffectSpecHandle Spec = SourceASC->MakeOutgoingSpec(DamageEffectClass,1,Context);
	if (!Spec.IsValid())return;
	//绑定蓝图里的set by caller magintude设置的Damage.Shoot
	Spec.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Damage.Shoot")), -DamageCount);

	//将效果作用到目标
	SourceASC->ApplyGameplayEffectSpecToTarget(*Spec.Data, TargetASC);
}
void UMyGASHelper::ApplyDamageToActor(AActor* SourceActor, AActor* TargetActor, float DamageCount, TSubclassOf<UGameplayEffect> DamageEffectClass)
{
	if (!SourceActor || !TargetActor) { UE_LOG(LogTemp, Warning, TEXT("NULL Actor")); return; }

	IAbilitySystemInterface* SourceInterface = Cast<IAbilitySystemInterface>(SourceActor);
	IAbilitySystemInterface* TargetInterface = Cast<IAbilitySystemInterface>(TargetActor);
	if (!SourceInterface|| !TargetInterface)  return;

	ApplyDamage(SourceInterface->GetAbilitySystemComponent(), TargetInterface->GetAbilitySystemComponent(), DamageCount, DamageEffectClass);
}
