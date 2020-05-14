// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGravityActor.h"

// Sets default values
AMyGravityActor::AMyGravityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyGravityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyGravityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

