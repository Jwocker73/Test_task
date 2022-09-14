// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyScoreUserWidget.generated.h"

UCLASS()
class MYPROJECT4_API UMyScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<APlayerState*> GetPlayersStates();
};
