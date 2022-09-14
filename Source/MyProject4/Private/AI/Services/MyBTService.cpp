// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/MyBTService.h"

#include "AIController.h"
#include "MyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTService::UMyBTService()
{
	NodeName = "Find Enemy";
}

void UMyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const auto cBlackboard = OwnerComp.GetBlackboardComponent();
	const auto cController = OwnerComp.GetAIOwner();
	if (!cBlackboard || !cController) return;

	const auto cPerceptionComponent = cController->FindComponentByClass<UMyAIPerceptionComponent>();
	if (cPerceptionComponent)
	{
		cBlackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, cPerceptionComponent->GetVisibleEnemyActor());
	}
}
