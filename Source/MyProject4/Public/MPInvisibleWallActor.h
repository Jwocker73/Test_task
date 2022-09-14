// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MPInvisibleWallActor.generated.h"

UCLASS()
class MYPROJECT4_API AMPInvisibleWallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMPInvisibleWallActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* CollisionComponent;
};
