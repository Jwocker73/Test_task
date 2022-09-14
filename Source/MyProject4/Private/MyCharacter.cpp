// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MPBullet.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainCharacter, All, All);

AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(GetRootComponent());
	
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	BulletsInMagazinNow = MaxBulletsInMagazin;	// Установка количества снарядов в максимальное количество снарядов в магазине.
	OnActorBeginOverlap.AddDynamic(this, &AMyCharacter::Respawn);	//Подключаем функцию респавна к делегату пересечения коллизий.
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMyCharacter::GetInfoAboutAmmo(int& CurrentBullets, int& DefaultBullets)
{
	CurrentBullets = BulletsInMagazinNow;
	DefaultBullets = MaxBulletsInMagazin;
	return true;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &AMyCharacter::Move);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Rotation", this, &AMyCharacter::Rotation);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shoot);
	PlayerInputComponent->BindAction("Turn", IE_Pressed, this, &AMyCharacter::Turn);
}

void AMyCharacter::Move(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AMyCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AMyCharacter::Rotation(float Amount)
{
	AddControllerYawInput(Amount * 1.5f);
}

void AMyCharacter::Turn()
{
	AddControllerYawInput(360.0f);
}

void AMyCharacter::Shoot()
{
	if (!GetWorld() || !bCanShoot) return;
	
	DecreaseBullets();											// Уменьшение снарядов при выстреле.
	const FVector C_Direction = GetActorRotation().Vector();	// Вектор направления полёта снаряда.

	const FTransform C_SpawnTransform(FRotator::ZeroRotator, StaticMesh->GetSocketLocation("MuzzleSocket"));	// Матрица трансформации для спавна снаряда.
	AMPBullet* Bullet = GetWorld()->SpawnActorDeferred<AMPBullet>(BulletClass, C_SpawnTransform); // Спавн снаряд с отложенным вызовом BeginPlay.
	if (Bullet)
	{
		Bullet->SetShotDirection(C_Direction);		// Устанавливает направления скорости MovementComponent'a у снаряда.
		Bullet->SetOwner(this);						// Устанавливает владельца, для проверки столкновения.
		Bullet->FinishSpawning(C_SpawnTransform);   // Конец спавна, вызов BeginPlay.
	}
	UGameplayStatics::SpawnSoundAttached(SCueShoot, StaticMesh, "MuzzleSocket");
	
}

void AMyCharacter::DecreaseBullets()
{
	BulletsInMagazinNow--;			// Уменьшаем количество снарядов.

	if (BulletsInMagazinNow == 0)	// Если количество снарядов достигло 0, то:
	{
		bCanShoot = false;	// Персонаж не может стрелять.
		UE_LOG(LogMainCharacter, Display, TEXT("-------------Reloading-------------"));
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &AMyCharacter::Reload, 1.0f);	// Выполнить перезарядку, через 1,5 секунды.
		UGameplayStatics::SpawnSoundAttached(SCueReload, StaticMesh, "MuzzleSocket");
	}
}

void AMyCharacter::Reload()
{
	UE_LOG(LogMainCharacter, Display, TEXT("------Magazin ready------"));
	BulletsInMagazinNow = MaxBulletsInMagazin;	// Перезарядка.
	bCanShoot = true;							// Персонаж может стрелять.
}

void AMyCharacter::Respawn(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OverlappedActor) return;

	OverlappedActor->SetActorLocation(RespawnPointLocation);
}

