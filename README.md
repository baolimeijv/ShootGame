# ShootGame — 多玩法模式的 UE5 游戏原型

UE5 项目，包含三个可切换的玩法模式（战斗 / 平台跳跃 / 横版卷轴）。
107 个 C++ 文件 / 约 5500 行。

## 技术要点

- **三套玩法模式**：Combat / Platforming / SideScrolling 各自独立的 GameMode、
  Character 与 PlayerController，共用 `BaseCharacter` 与 `HealthComponent`
- **敌人 AI**：行为树任务 `BTTask_FindPlayer`（追踪玩家）+ `BTTask_Shoot`（射击），
  配合 EQS 查询上下文 `EnvQueryContext_Player` 做位置决策；
  战斗敌人另有 StateTree 驱动的状态机（`CombatStateTreeUtility`）
- **战斗判定由动画通知驱动**：`AnimNotify_DoAttackTrace` 攻击轨迹检测、
  `AnimNotify_CheckCombo` 连招窗口、`AnimNotify_CheckChargedAttack` 蓄力判定、
  `AnimNotify_EndDash` 冲刺结束
- **GAS**：`MyAttributeSet` + `MyGASHelper` 管理血量与属性
- **关卡机制**：检查点、伤害盒、熔岩地板、激活触发器、拾取物、跳板、
  移动平台、软平台、可交互 NPC
- **横版相机**：`SideScrollingCameraManager` 负责跟随与边界约束

## 项目结构

```
Source/ShootGame/
├── Combat*          # 战斗模式：角色、敌人、AI、生命条、生成器、检查点、伤害盒
├── Platforming*     # 平台跳跃模式
├── SideScrolling*   # 横版模式：角色、AI、相机、拾取、跳板、移动平台、UI
├── BTTask_*         # 行为树任务：追踪玩家 / 射击
├── EnvQuery*        # EQS 查询上下文
├── AnimNotify_*     # 动画通知：攻击轨迹 / 连招 / 蓄力 / 冲刺
└── MyGAS*           # GAS 属性集与辅助
```

## 构建

需要 Unreal Engine 5，用编辑器打开 `ShootGame.uproject`（首次会编译 C++ 模块）。
