// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter/Player/BasePlayerAnimInstance.h"
#include"BasePlayer.h"
#include"GameFrameWork/CharacterMovementComponent.h"

void UBasePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Player = Cast<ABasePlayer>(TryGetPawnOwner());
}

void UBasePlayerAnimInstance::UpdateAnim(float DeltaTime)
{
	if (Player == nullptr)
	{
		Player = Cast<ABasePlayer>(TryGetPawnOwner());
	}
	else
	{
		FVector PlayerVelocity = Player->GetVelocity();
		F_Speed = PlayerVelocity.Size();
		B_isAir = Player->GetCharacterMovement()->IsFalling();
		FVector PlayerAcceleration = Player->GetCharacterMovement()->GetCurrentAcceleration();
		F_Acceleration = PlayerAcceleration.Size();
		//并非物理加速度
		if (F_Acceleration > 0.f)
		{
			B_isMove = true;
		}
		else
		{
			B_isMove = false;
		}
	}
}
