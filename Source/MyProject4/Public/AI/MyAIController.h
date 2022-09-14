// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UMyAIPerceptionComponent;
class APlayerStart;

UCLASS()
class MYPROJECT4_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMyAIPerceptionComponent* MyAIPerceptionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName ActorEnemyKey = "EnemyActor";   // Имя ключа, указывающего на врага.

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	AActor* GetFocusOnActor() const;
};
