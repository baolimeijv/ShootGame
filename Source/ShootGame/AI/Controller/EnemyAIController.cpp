#include "AI/Controller/EnemyAIController.h"
#include"BehaviorTree/BehaviorTree.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviorTree = nullptr;
	Blackboard = nullptr;
}

//绑定结构：Controller->BehaviorTree->BlackBoard
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BehaviorTree)
	{
		UBlackboardComponent* BB = GetBlackboardComponent();
		if (!BB)
		{
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardCom);
		}
		RunBehaviorTree(BehaviorTree);
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//获得大脑组件执行停止
	if (UBehaviorTreeComponent* BT_Com = Cast<UBehaviorTreeComponent>(GetBrainComponent()))
	{
		BT_Com->StopTree(EBTStopMode::Safe);
	}
}