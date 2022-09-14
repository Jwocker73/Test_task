// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MenuUserWidget.h"
#include "MyGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

class UMyGameInstance;

bool UMenuUserWidget::Initialize()
{
	const auto cInitStatus = Super::Initialize();
	if (StartGame)
	{
		StartGame->OnClicked.AddDynamic(this, &UMenuUserWidget::StartGameFunction);
	}
	
	if (ExitGame)
	{
		ExitGame->OnClicked.AddDynamic(this, &UMenuUserWidget::ExitGameFunction);
	}
	
	return cInitStatus;
}

void UMenuUserWidget::StartGameFunction()
{
 	const auto cGameInstance = GetWorld()->GetGameInstance<UMyGameInstance>();
	if (!cGameInstance) return;
	
	UGameplayStatics::OpenLevel(this, cGameInstance->GetLevelGameName());
}

void UMenuUserWidget::ExitGameFunction()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
