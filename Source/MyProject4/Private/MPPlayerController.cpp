// Fill out your copyright notice in the Description page of Project Settings.

#include "MPPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void AMPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameOnly());
}

void AMPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("Exit", IE_Pressed, this, &AMPPlayerController::ExitGame);
}

void AMPPlayerController::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, true);
}
