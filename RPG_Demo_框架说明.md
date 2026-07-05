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
### 2. 解决ATTRIBUTE_ACCESSORS报错
- 添加 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)