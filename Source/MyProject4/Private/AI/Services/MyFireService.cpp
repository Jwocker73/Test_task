// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/MyFireService.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyFireService::UMyFireService()
{
	NodeName = "Fire";
}

void UMyFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	const auto cBlackboard = OwnerComp.GetBlackboardComponent();
	const auto cController = OwnerComp.GetAIOwner();
	if (!cBlackboard || !cController) return;

	if (Cast<AMyCharacter>(cBlackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName)))
	{
		const auto cAIPawn = Cast<AMyCharacter>(cController->GetPawn());
		if (cAIPawn)
		{
			cAIPawn->Shoot();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
