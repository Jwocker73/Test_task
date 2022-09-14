// Fill out your copyright notice in the Description page of Project Settings.

#include "MPInvisibleWallActor.h"

AMPInvisibleWallActor::AMPInvisibleWallActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);			// Без физических взаимодействий, только оповещения.
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	// Блокирока коллизии для всех каналов.
}

void AMPInvisibleWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

