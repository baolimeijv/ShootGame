// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTGAME_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:
	void ShootAtPlayer(AActor* Target);
	FVector GetEnemyLocation() const;
};
