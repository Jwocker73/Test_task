// Fill out your copyright notice in the Description page of Project Settings.


#include "MPBullet.h"
#include "MPGameModeBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MPInvisibleWallActor.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "Kismet/GameplayStatics.h"

AMPBullet::AMPBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);	
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);		// Физические взаимодействия и оповещения.
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	// Блокирока коллизии для всех каналов.
	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.0f;			// Начальная скорость снаряда 1000.
	MovementComponent->ProjectileGravityScale = 0.0f;	// Гравитация не действует на снаряд.
	MovementComponent->bShouldBounce = true;			// Снаряд будет отскакивать.
	MovementComponent->Bounciness = 1.0f;				// Снаряд не будет терять скорость при отскоке.
	MovementComponent->Friction = 0.0f;					// Сила трения не действует на снаряд при отскоке.
}

void AMPBullet::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);	// Проверка компонентов.
	check(CollisionComponent);	
	
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;		// Установка вектора скорости движения снаряда.
}

void AMPBullet::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	const auto cHitCharacter = Cast<AMyCharacter>(Other);
	if (!cHitCharacter)		// Если попали не в Персонажа, то:
	{
		const auto cHitInvisibleWallActor = Cast<AMPInvisibleWallActor>(Other);
		if (cHitInvisibleWallActor)	// Если попали в границу, то:
		{
			Destroy();	// Уничтожаем пулю.
		}
		return;
	}

	// Если попали в персонажа:
	MovementComponent->StopMovementImmediately();	// Останавливаем пулю.
	const auto cCharacter = Cast<AMyCharacter>(GetOwner());
	if (!cCharacter) return;
	
	ACharacter* CurrentWinner = nullptr;
	if (cCharacter == cHitCharacter)
	{
		TArray<AActor*> AllCharacters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMyCharacter::StaticClass(),AllCharacters);
		for (const auto cOneCharacter : AllCharacters)
		{
			const auto cThisCharacter = Cast<AMyCharacter>(cOneCharacter);
			if (!cThisCharacter || cThisCharacter == cCharacter) continue;
			CurrentWinner = cThisCharacter;
		}
	}
	else
	{
		CurrentWinner = cCharacter;
	}
	const auto cMyPlayerState = Cast<AMyPlayerState>(CurrentWinner->GetPlayerState());
	if (cMyPlayerState)
	{
		// Set a new score.
		cMyPlayerState->ImplementKillsNum();
		const auto cMPGameModeBase = Cast<AMPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (cMPGameModeBase)
		{
			// Respawn players;
			cMPGameModeBase->ResetPlayers();
		}
	}
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SCueDamage, GetActorLocation());
	Destroy();	// Уничтожение пули.
}
