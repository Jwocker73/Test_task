// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameModeBase.generated.h"

class USoundCue;

UCLASS()
class MYPROJECT4_API AMPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMPGameModeBase();
	virtual void StartPlay() override;  // Start before all function, even BeginPlay.
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override; // For spawn bots by AI character class.
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	void ResetPlayers();
	TArray<AController*> GetPlayersControllers();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Game")
	int32 NumOfPlayers = 2;
	
	UPROPERTY(EditAnywhere, Category = "Game")
	TSubclassOf<AController> AIControllerClass;
	
	UPROPERTY(EditAnywhere, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SCueStart;

private:
	void SpawnBots();
	void ResetOnePlayer(AController* Controller);
	
};
