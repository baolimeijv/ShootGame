#include "BaseCharacter/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/HealthComponent.h"
#include"Components/CapsuleComponent.h"
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::ShootAtPlayer(AActor* Target)
{
	if (!Target) return;

	//AI->Player Location
	const FVector StartLocation = GetMesh()->GetSocketLocation("index_03_l");
	FVector TargetLocation = Target->GetActorLocation();
	FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
	FVector EndLocation = StartLocation + Direction * 2000.f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// 发射射线检测
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);

	// 如果命中，尝试造成伤害
	if (HitResult.bBlockingHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->TakeDamage(10.f, this);
		}

		// 调试可视化
		DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Red, false, 1.f);
		DrawDebugPoint(GetWorld(), HitResult.Location, 10.f, FColor::Green, false, 1.f);
	}
	else
	{
		// 未命中，画一条淡蓝色的线显示开枪方向
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 0.5f);
	}
}

FVector AEnemy::GetEnemyLocation() const
{
	return GetActorLocation();
}
