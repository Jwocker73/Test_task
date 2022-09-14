// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	
}