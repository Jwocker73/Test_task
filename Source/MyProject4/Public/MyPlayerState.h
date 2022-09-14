// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

UCLASS()
class MYPROJECT4_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	void SetKillsNum(int32 NewKillsNum) { KillsNum = NewKillsNum; }
	void ImplementKillsNum() { ++KillsNum; }

	UFUNCTION(BlueprintCallable)
	int32 GetKillsNum() const { return KillsNum; }
	
private:
	int32 KillsNum = 0;
};
