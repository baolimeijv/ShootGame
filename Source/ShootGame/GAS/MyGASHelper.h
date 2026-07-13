// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyGASHelper.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class SHOOTGAME_API UMyGASHelper : public UObject
{
	GENERATED_BODY()
	
public:
	static void ApplyDamage(UAbilitySystemComponent* SourceASC,UAbilitySystemComponent* TargetASC,float DamageCount,TSubclassOf<UGameplayEffect>DamageEffectClass);
	static void ApplyDamageToActor(AActor *SourceActor,AActor *TargetActor,float DamageCount,TSubclassOf<UGameplayEffect>DamageEffectClas);

};
