#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" 
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UAbilitySystemComponent;
class UMyAttributeSet;

UCLASS()
class SHOOTGAME_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	//GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}
	
	//角色技能
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	//属性设置容器存储数据，不实现逻辑
	UPROPERTY()
	TObjectPtr<UMyAttributeSet>MyAttributeSet;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//业务层实现逻辑
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> Health;

};
