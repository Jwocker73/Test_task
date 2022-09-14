// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIPerceptionComponent.h"
#include "MyCharacter.h"
#include "Perception/AISense_Sight.h"

AActor* UMyAIPerceptionComponent::GetVisibleEnemyActor() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() != 0)
	{
		for (const auto cPercieveActor : PercieveActors)
		{
			if (Cast<AMyCharacter>(cPercieveActor))
				return cPercieveActor;
		}
	}
	return nullptr;
}
