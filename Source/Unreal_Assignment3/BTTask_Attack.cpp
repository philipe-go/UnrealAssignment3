// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* MyEnemy = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));

	if (MyEnemy)
	{
		MyEnemy->onAttack();
		return EBTNodeResult::Succeeded;
	}

	GEngine->AddOnScreenDebugMessage(0, 4, FColor::Blue, TEXT("AI Task Failed"));
	return EBTNodeResult::Failed;
}
