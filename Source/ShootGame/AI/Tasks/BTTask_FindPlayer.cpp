#include "AI/Tasks/BTTask_FindPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    APawn* Pawn = AIC->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return EBTNodeResult::Failed;

    AActor* PlayerPawn = PC->GetPawn();
    if (!PlayerPawn) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (BB)
    {
        BB->SetValueAsObject("TargetActor", PlayerPawn);
        BB->SetValueAsBool("CanSeePlayer", true);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

