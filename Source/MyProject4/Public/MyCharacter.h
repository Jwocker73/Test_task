// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MPBullet.h"
#include "Sound/SoundCue.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class UStaticMeshComponent;
class USpringArmComponent;

UCLASS()
class MYPROJECT4_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Ammo", meta = (ClampMin = "1"))
	int32 MaxBulletsInMagazin = 4;			// Максимальное количество снарядов в магазине.

	UPROPERTY(EditAnywhere, Category = "Ammo")
	TSubclassOf<AMPBullet> BulletClass;		// Класс снаряда, которым стреляет персонаж.
	
	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	FVector RespawnPointLocation = FVector(0.0f, 0.0f, 0.0f);			// Стандартная позиция респавна персонажа.
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SCueShoot;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SCueReload;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool GetInfoAboutAmmo(int& CurrentBullets, int& DefaultBullets);
	bool IsCanShoot() const { return bCanShoot; }
	void Shoot();					// Функция, которая отвечает за стрельбу.

private:
	void Move(float Amount);		// Функция, которая отвечает за движение.
	void MoveRight(float Amount);	// Функция, которая отвечает за движение в бок.
	void Rotation(float Amount);	// Функция, которая отвечает за поворот.
	void Turn();					// Функция, которая отвечает за разворот.
	void DecreaseBullets();			// Функция, которая отвечает за уменьшение снарядов в магазине.
	void Reload();					// Функция, которая отвечает за перезарядку.
	bool bCanShoot = true;			// Переменная, показывающая возможность стрелять.
	FTimerHandle ReloadTimer;		// Переменная типа FTimerHandle, отвечающая за таймер перед перезарядкой (Для иллюзии перезарядки).
	int32 BulletsInMagazinNow;				// Количество снарядов на данный момент.
	
	UFUNCTION()
	void Respawn(AActor* OverlappedActor, AActor* OtherActor);	// Функция респавна персонажа при пересечении границ поля.
};
