// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MyHUD.h"
#include "Blueprint/UserWidget.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto cPlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass);
	if (cPlayerWidget)
	{
		cPlayerWidget->AddToViewport();
	}
}
