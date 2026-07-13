// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy.generated.h"

class UGameplayEffect;


UCLASS()
class SHOOTGAME_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemy();
	//GAS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TSubclassOf<UGameplayEffect>DamageEffectClass;

protected:
	virtual void BeginPlay() override;

public:
	void ShootAtPlayer(AActor* Target);
	FVector GetEnemyLocation() const;
};
