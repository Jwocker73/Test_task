// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS()
class MYPROJECT4_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetInfoAboutAmmo(int& CurrentBullets, int& DefaultBullets);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsCanShoot();
	
};
