// Fill out your copyright notice in the Description page of Project Settings.

#include "MPGameModeBase.h"
#include "AIController.h"
#include "MyCharacter.h"
#include "MPPlayerController.h"
#include "MyAIController.h"
#include "MyPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "HUD/MyHUD.h"
#include "Kismet/GameplayStatics.h"

AMPGameModeBase::AMPGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMPPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	NumOfPlayers = 2;
}

void AMPGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	UGameplayStatics::PlaySound2D(GetWorld(), SCueStart);
	SpawnBots();
}

UClass* AMPGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* AMPGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	const bool bIsAiController = (Cast<AMyAIController>(Player) ? true : false);
	for (auto PlayerStart : PlayerStarts)
	{
		if (bIsAiController)
		{
			if (Cast<APlayerStart>(PlayerStart)->PlayerStartTag == "Enemy")
			{
				return PlayerStart;
			}
		}
		else
		{
			if (Cast<APlayerStart>(PlayerStart)->PlayerStartTag == "Main")
			{
				return PlayerStart;
			}
		}
	}
	
	return Super::ChoosePlayerStart_Implementation(Player);
}

void AMPGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int index = 0; index < NumOfPlayers - 1; ++index)
	{
		FActorSpawnParameters SpawnInfo;                                                            // Можно указать параметры спавна коллизий.
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Данный параметр спавнит ни смотря ни на что.

		const auto cMyAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);    // Spawn AI controllers by AIControllerClass and param of SpawnInfo.
		RestartPlayer(cMyAIController);
	}
}

void AMPGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;
	
	TArray<AActor*> AllBulletActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMPBullet::StaticClass(),AllBulletActors);
	for (int index = 0; index < AllBulletActors.Num(); ++index)
	{
		GetWorld()->DestroyActor(AllBulletActors[index]);
	}
	
	// For all controllers.
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AMPGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		// Destroy alive character.
		Controller->GetPawn()->Reset();
	}
	// Restart character.
	RestartPlayer(Controller);
}

TArray<AController*> AMPGameModeBase::GetPlayersControllers()
{
	TArray<AController*> Controllers;
	if (!GetWorld()) return Controllers;

	// For all controllers.
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		Controllers.Add(It->Get());
	}
	return Controllers;
}