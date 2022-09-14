// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USoundCue;

UCLASS()
class MYPROJECT4_API AMPBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	AMPBullet();
	void SetShotDirection(const FVector& NewShotDirection) { ShotDirection = NewShotDirection; }
	
protected:
	virtual void BeginPlay() override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MovementComponent;    // Логический компонент движения.
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SCueDamage;

private:
	FVector ShotDirection;					// Вектор направления для настройки Velocity.
};
