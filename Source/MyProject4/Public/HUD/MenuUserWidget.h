// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;

UCLASS()
class MYPROJECT4_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGame;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGame;

private:
	UFUNCTION()
	void StartGameFunction();
	
	UFUNCTION()
	void ExitGameFunction();
};
