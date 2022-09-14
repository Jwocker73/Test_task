// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameModeBase.h"
#include "MenuPlayerController.h"
#include "MyHUD.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}
