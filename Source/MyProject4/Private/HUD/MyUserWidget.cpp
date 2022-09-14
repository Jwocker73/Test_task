// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MyUserWidget.h"
#include "MyCharacter.h"

bool UMyUserWidget::GetInfoAboutAmmo(int& CurrentBullets, int& DefaultBullets)
{
	const auto cCharacter = Cast<AMyCharacter>(GetOwningPlayer()->GetPawn());
	if (!cCharacter) return false;

	return cCharacter->GetInfoAboutAmmo(CurrentBullets, DefaultBullets);
}

bool UMyUserWidget::IsCanShoot()
{
	const auto cCharacter = Cast<AMyCharacter>(GetOwningPlayer()->GetPawn());
	if (!cCharacter) return false;

	return cCharacter->IsCanShoot();
}
