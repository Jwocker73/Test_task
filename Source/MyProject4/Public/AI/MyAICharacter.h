// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class MYPROJECT4_API AMyAICharacter : public AMyCharacter
{
	GENERATED_BODY()

public:
	AMyAICharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;   // Указатель на дерево поведения, для спавна логики через контроллер.
	
};
