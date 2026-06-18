

#include "BasePlayer.h"

#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include"Engine/LocalPlayer.h"
#include"EnhancedInputComponent.h"
#include "InputActionValue.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Sound/SoundCue.h"
#include"Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Animation/AnimMontage.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraBoom = CreateDefaultSubobject<USpringArmComponent>("PlayerCameraBoom");
	PlayerCameraBoom->SetupAttachment(RootComponent);
	PlayerCameraBoom->TargetArmLength = 200.0f;
	//注意这里是跟着准星旋转不是角色
	PlayerCameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(PlayerCameraBoom);
	PlayerCamera->bUsePawnControlRotation = false;

	//这里是让角色不跟准星旋转
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);

}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	//注册增强输入子系统
	APlayerController* PlayerControl = Cast<APlayerController>(Controller);
	if (PlayerControl)
	{
		UEnhancedInputLocalPlayerSubsystem* LocalSS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControl->GetLocalPlayer());
		if (LocalSS)
		{
			LocalSS->AddMappingContext(PlayerInputMapping,0);
		}

		PlayerControl->PlayerCameraManager->ViewPitchMax = 30.f;
		PlayerControl->PlayerCameraManager->ViewPitchMin = -60.f;
	}

	
}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(PlayerMove, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
		EnhancedInputComponent->BindAction(PlayerLook, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
		EnhancedInputComponent->BindAction(PlayerJump, ETriggerEvent::Started, this, &ABasePlayer::Jump);
		EnhancedInputComponent->BindAction(PlayerJump, ETriggerEvent::Completed, this, &ABasePlayer::StopJumping);
		EnhancedInputComponent->BindAction(PlayerShoot, ETriggerEvent::Triggered, this, &ABasePlayer::Shoot);
	}

}

void ABasePlayer::Move(const FInputActionValue& Value)
{
	//原点左上，x右，y下
	const FVector2D F2d = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Ro = Controller->GetControlRotation();
		const FRotator YawRo(0, Ro.Yaw, 0);
		const FVector PlayerF = FRotationMatrix(YawRo).GetUnitAxis(EAxis::X);
		const FVector PlayerR = FRotationMatrix(YawRo).GetUnitAxis(EAxis::Y);
		AddMovementInput(PlayerF, F2d.Y);	
		AddMovementInput(PlayerR, F2d.X);

	}

}

void ABasePlayer::Look(const FInputActionValue& Value)
{
	const FVector2D F2d = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerPitchInput(F2d.Y);
		AddControllerYawInput(F2d.X);
	}
}

void ABasePlayer::Shoot(const FInputActionValue& Value)
{
	//音效
	if (ShootSound)
	{
		UGameplayStatics::PlaySound2D(this, ShootSound);
	}
	
	//粒子效果
	//const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("MuzzleSocket");
	const FVector SocketLoaction = GetMesh()->GetSocketLocation("MuzzleSocket");
	const FRotator SocketRotation = GetMesh()->GetSocketRotation("MuzzleSocket");
	const FVector SocketScale(0.5f,0.5f,0.5f);

	//if (MuzzleSocket)
	//{
		//获得变换信息
		//const FTransform MuzzleSocketTransform = MuzzleSocket->GetSocketTransform(GetMesh());
		if (P_ShootMuzzle)
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_ShootMuzzle, MuzzleSocketTransform);
			UGameplayStatics::SpawnEmitterAttached(P_ShootMuzzle, GetMesh(), "MuzzleSocket",
				SocketLoaction, SocketRotation, SocketScale, EAttachLocation::KeepWorldPosition);
		}
	//}
	
	//蒙太奇动画射击
	UAnimInstance* PlayerAnimInstance = GetMesh()->GetAnimInstance();
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->Montage_Play(AM_Shoot);
		
	}
}

