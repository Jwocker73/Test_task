// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"
#include "MyAICharacter.h"
#include "MyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig.h"

AMyAIController::AMyAIController()
{
	MyAIPerceptionComponent = CreateDefaultSubobject<UMyAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*MyAIPerceptionComponent); // Установка компонента чувств в классе контроллера.
	bWantsPlayerState = true;
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto cMyAICharacter = Cast<AMyAICharacter>(InPawn);
	if (cMyAICharacter)
	{
		RunBehaviorTree(cMyAICharacter->BehaviorTreeAsset);
	}
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto cFocusActor = GetFocusOnActor();
	SetFocus(cFocusActor);
}

AActor* AMyAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(ActorEnemyKey));
}
