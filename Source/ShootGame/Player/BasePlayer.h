
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer.generated.h"

struct FInputActionValue;
class USoundCue;
class UParticleSystem;
class UAnimMontage;

UCLASS()
class SHOOTGAME_API ABasePlayer : public ACharacter
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

	//射击音效粒子播放
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class USoundCue* ShootSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* P_ShootMuzzle;
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
protected:
	virtual void BeginPlay() override;

	

};
