
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter/BaseCharacter.h"
#include "BasePlayer.generated.h"

struct FInputActionValue;
class USoundCue;
class UParticleSystem;
class UAnimMontage;
class ABaseCharacter;
class UGameplayEffect;

UCLASS()
class SHOOTGAME_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
private:
	//相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCaeram", meta = (AllowPrivateAccess="true"))
	class USpringArmComponent *PlayerCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess="true"))
	class UCameraComponent* PlayerCamera;

	//增强输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess="true"))
	class UInputMappingContext* PlayerInputMapping;

	//行为
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PlayerMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PlayerLook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PlayerJump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess="true"))
	class UInputAction* PlayerShoot;

	//射击音效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class USoundCue* ShootSound;

	//射击粒子
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* P_ShootMuzzle;
	//击中
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* P_ShootHit;
	//射击线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* P_ShootBeam;

	//射击动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
    class UAnimMontage* AM_Shoot;

	

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
public:
	ABasePlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//GAS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	 TSubclassOf<UGameplayEffect> DamageEffectClass;

protected:
	virtual void BeginPlay() override;

	

};
