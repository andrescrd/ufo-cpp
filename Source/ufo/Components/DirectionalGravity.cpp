// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalGravity.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
#include "ufo\Interfaces\Attraction.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDirectionalGravity::UDirectionalGravity()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDirectionalGravity::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, UAttraction::StaticClass(), Actors);

	TArray<UStaticMeshComponent*> Comp;
	GetOwner()->GetComponents<UStaticMeshComponent>(Comp);

	mesh = Comp[0];

	if (Actors.Num() > 0)
		actor = Actors[0];
}

// Called every frame
void UDirectionalGravity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator rotator = (UKismetMathLibrary::FindLookAtRotation(actor->GetActorLocation(), GetOwner()->GetActorLocation()));
	FVector lookAtVector = UKismetMathLibrary::GetForwardVector(rotator);

	FMatrix matrix = FRotationMatrix::MakeFromZX(lookAtVector, GetOwner()->GetActorForwardVector());
	GetOwner()->SetActorRotation(matrix.Rotator());

	mesh->SetPhysicsLinearVelocity(lookAtVector * -1 * gravity, true);
}

