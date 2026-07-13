# 整体架构（2026.6.15）
## BasePlayer
- 角色移动跳越动画
- 射击功能（开火粒子火花，开火音效，击中弹道特效）
- 达芬奇射击动作
## HealthComponent
- 加入血量组件方便后面复用
## AI->Enemy
- EnemyAIContorller:敌人的控制器
- 黑板组件：添加玩家Actor
- 行为树:BTTask_FindPlayer-->Move to-->BTTask_Shoot
- 注意：要加入导航网格体不然敌人不会动
## GAS系统
### 1. 解决ue没有UAttributeSet问题
- 在ShootGame.Build.cs的PublicDependencyModuleNames.AddRange中加入"GameplayAbilities","GameplayTags","GameplayTasks"
- 在ue中下载插件"GameplayAbilities"
### 2.MyAttributeSet
- 定义宏辅助函数：
   `添加 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)`
- 用辅助函数宏初始化血量:`InitHealth(100.f);
	InitMaxHealth(100.f);`
- 钳制Health和MaxHealth`void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)`
- 死亡判断销毁实体:`virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;`
### 3. GAS射击调用流程
- 发出者击中后触发伤害调用`UMyGASHelper::ApplyDamageToActor(this, HitActor, 20.f, DamageEffectClass);`
将Actor转换为ASI在获得ASC
- 再把ASC传入`void UMyGASHelper::ApplyDamage(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC, float DamageCount, TSubclassOf<UGameplayEffect> DamageEffectClass)`
### 4.角色属性设置，技能系统
- 为了良好的复用性，写在BaseCharacter里面
- 为了获得之前技能组件里的数据要重写`virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override{return AbilitySystemComponent;}`
- 由于角色想要实现角色技能释放，血量属性参数复用性良好，以及一些游戏属性逻辑，需要用到`UAbilitySystemComponent` `UAttributeSet` `UHealthComponent`
- 对组件进行初始化之后要在游戏开始，进行注入注册表
