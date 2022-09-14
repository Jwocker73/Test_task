// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MyScoreUserWidget.h"
#include "MPGameModeBase.h"

TArray<APlayerState*> UMyScoreUserWidget::GetPlayersStates()
{
	TArray<APlayerState*> PlayerStates;
	TArray<AController*> Controllers;
	if (!GetWorld()) return PlayerStates;

	const auto cMyGameMode = Cast<AMPGameModeBase>(GetWorld()->GetAuthGameMode());
	Controllers = cMyGameMode ? cMyGameMode->GetPlayersControllers() : Controllers;

	for (int index = 0; index < Controllers.Num(); ++index)
	{
		PlayerStates.Push(Controllers[index]->PlayerState);
	}
	
	return PlayerStates;
}
