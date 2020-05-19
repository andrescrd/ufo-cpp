// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerFly.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/RotateAroundActor.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AMyPlayerFly::AMyPlayerFly()
{
	//PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->AddRelativeLocation(FVector(0, 0, 0));
	Body->SetupAttachment(GetRootComponent());
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(true);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1);
	Body->SetConstraintMode(EDOFMode::XZPlane);

	RotateAroundActor = CreateDefaultSubobject<URotateAroundActor>("RotateAroundActor");
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
//}

void AMyPlayerFly::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayerFly::Rotate);
	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayerFly::StartBoost);
	playerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayerFly::StopBoost);
}

void AMyPlayerFly::Rotate(float value)
{
	FRotator rotator = FRotator(value * rotationVelocity * GetWorld()->GetDeltaSeconds(), 0, 0);
	AddActorLocalRotation(rotator, true);
}

void AMyPlayerFly::StartBoost()
{
	if (isInRotationZone)
		DeactivateRotation();

	GetWorldTimerManager().SetTimer(boostTimerHadle, this, &AMyPlayerFly::BoostTimer, 1, true);
}

void AMyPlayerFly::BoostTimer()
{
	fastBoostForceCounter += fastBoostForce;
}

void AMyPlayerFly::StopBoost()
{
	GetWorldTimerManager().ClearTimer(boostTimerHadle);

	FVector BoostVelocity = GetActorUpVector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
	fastBoostForceCounter = 0;
}

void AMyPlayerFly::OnRotationZone(AActor* other)
{
	UE_LOG(LogTemp, Warning, TEXT("rotation zone"));
	isInRotationZone = true;
	RotateAroundActor->rotateAroundActor = other;
	RotateAroundActor->Activate();
}

void AMyPlayerFly::DeactivateRotation()
{
	isInRotationZone = false;
	RotateAroundActor->Deactivate();
	RotateAroundActor->rotateAroundActor = nullptr;
}

