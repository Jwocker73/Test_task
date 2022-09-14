// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Contexts/MyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UMyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const auto cQueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	const auto cBlackboard = UAIBlueprintHelperLibrary::GetBlackboard(cQueryOwner);
	if (!cBlackboard) return;

	const auto cContextActor = cBlackboard->GetValueAsObject(EnemyActorKey);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(cContextActor));
}
