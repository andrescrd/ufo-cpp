// Fill out your copyright notice in the Description page of Project Settings.

#include "ufo\MyPlayerFly.h"
#include "Components\SphereComponent.h"
#include "PointOfRotation.h"

// Sets default values
APointOfRotation::APointOfRotation()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(GetRootComponent());
}

void APointOfRotation::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APointOfRotation::OnOverlap);
}


void APointOfRotation::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayerFly* player = Cast<AMyPlayerFly>(OtherActor);

	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("rotation zone, player"));

		player->OnRotationZone(this);
	}
}
