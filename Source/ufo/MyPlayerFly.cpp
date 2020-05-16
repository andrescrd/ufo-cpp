// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerFly.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AMyPlayerFly::AMyPlayerFly()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(GetRootComponent());
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1);
	Body->SetConstraintMode(EDOFMode::XYPlane);

}

//// Called when the game starts or when spawned
//void AMyPlayerFly::BeginPlay()
//{
//	Super::BeginPlay();
//
//}

//// Called every frame
//void AMyPlayerFly::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AMyPlayerFly::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayerFly::Rotate);
	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayerFly::StartBoost);
	playerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayerFly::StopBoost);
}

void AMyPlayerFly::Rotate(float value)
{
	FRotator rotator = FRotator(0, value * rotationVelocity * GetWorld()->GetDeltaSeconds(), 0);
	AddActorLocalRotation(rotator, true);
}

void AMyPlayerFly::StartBoost()
{
	GetWorldTimerManager().SetTimer(boostTimerHadle, this, &AMyPlayerFly::BoostTimer, 1, true);
}

void AMyPlayerFly::BoostTimer()
{
	fastBoostForceCounter += fastBoostForce;
}

void AMyPlayerFly::StopBoost()
{
	GetWorldTimerManager().ClearTimer(boostTimerHadle);

	FVector BoostVelocity = GetActorRotation().Vector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
	fastBoostForceCounter = 0;
}

