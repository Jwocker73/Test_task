// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/MyAICharacter.h"
#include "MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyAICharacter::AMyAICharacter()
{
	AIControllerClass = AMyAIController::StaticClass();
	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
	}
}