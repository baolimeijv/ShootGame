#include "GAS/MyAttributeSet.h"
#include"GameplayEffectExtension.h"
#include "Components/HealthComponent.h"

UMyAttributeSet::UMyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute()) 
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
}

//敌人打不死玩家穿模下坠
//void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
//{
//    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
//    {
//        if (GetHealth() <= 0.f)
//        {
//            AActor* Owner = GetOwningActor();
//            if (Owner)
//            {
//                UHealthComponent* HC = Owner->FindComponentByClass<UHealthComponent>();
//                if (HC)
//                {
//                    HC->OnDeath.Broadcast();  // 蓝图委托，UI 血条等会收到
//
//                    // 禁用碰撞
//                    UCapsuleComponent* Capsule = Owner->FindComponentByClass<UCapsuleComponent>();
//                    if (Capsule)
//                    {
//                        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//                    }
//
//                    // 延迟销毁
//                    Owner->SetLifeSpan(0.5f);
//                }
//            }
//        }
//    }
//}

//打死敌人卡退
//void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
//{
//    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
//    {
//        if (GetHealth() <= 0.f)
//        {
//            AActor* Owner = GetOwningActor();
//            if (!Owner) return;
//
//            // 防重复执行
//            if (Owner->IsActorBeingDestroyed()) return;
//
//            // 蓝图死亡回调
//            UHealthComponent* HC = Owner->FindComponentByClass<UHealthComponent>();
//            if (HC)
//            {
//                HC->OnDeath.Broadcast();
//            }
//
//            APawn* PawnOwner = Cast<APawn>(Owner);
//            if (!PawnOwner) return;
//
//            // 敌人：直接销毁，UE 自己清理 AI/BT
//            if (PawnOwner->IsPlayerControlled() == false)
//            {
//                Owner->Destroy();
//            }
//            else
//            {
//                // 玩家：冻结输入和移动
//                if (APlayerController* PC = PawnOwner->GetController<APlayerController>())
//                {
//                    PC->DisableInput(PC);
//                }
//            }
//        }
//    }
//}

//死亡逻辑
void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        if (GetHealth() <= 0.f)
        {
            AActor* Owner = GetOwningActor();
            if (!Owner) return;
            if (Owner->IsActorBeingDestroyed()) return;
            if (bDead) return;
            bDead = true;

            //拿到血量组件进行广播死亡
            UHealthComponent* HC = Owner->FindComponentByClass<UHealthComponent>();
            if (HC) HC->OnDeath.Broadcast();

            //下帧销毁
            Owner->GetWorldTimerManager().SetTimerForNextTick(
                FTimerDelegate::CreateLambda([Owner]()
                    {
                        if (IsValid(Owner))
                        {
                            Owner->Destroy();
                        }
                    })
            );
        }
    }
}