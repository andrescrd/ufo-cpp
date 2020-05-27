#include "MyPlayerFly.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "ufo/Enemies/MyProjectile.h"
#include "Player/PlayerBase.h"
#include "ufo/ufoGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"

AMyPlayerFly::AMyPlayerFly() : APlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetConstraintMode(EDOFMode::XZPlane);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Body;
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 3000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	initialArmLength = SpringArm->TargetArmLength;
}

void AMyPlayerFly::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = GetWorld()->GetAuthGameMode<AufoGameModeBase>();
	OnActorBeginOverlap.AddDynamic(this, &AMyPlayerFly::OnOverlap);
}

void AMyPlayerFly::Tick(float DeltaTime)
{
	if (isAlive)
	{
		if (!distanceReached)
		{
			distance += DeltaTime * velocity / 100;

			if (distance >= CurrentGameMode->DistanceToReach)
			{
				distanceReached = true;
				CurrentGameMode->LevelComplete();
			}
		}
	}
	else
	{
		CurrentGameMode->EndGame();
	}
}

void AMyPlayerFly::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayerFly::Rotate);
	playerInputComponent->BindAxis("Vertical", this, &AMyPlayerFly::VerticalMovement);

	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayerFly::StartBoost);
	playerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayerFly::StopBoost);
}

void AMyPlayerFly::VerticalMovement(float value)
{
	FVector movment = FVector(0, 0, value * velocity * GetWorld()->GetDeltaSeconds());
	//Body->AddImpulse(movment, NAME_None, true);
	AddActorLocalOffset(movment, true);
}

void AMyPlayerFly::Rotate(float value)
{
	FRotator componentRotation = SpringArm->GetComponentRotation();
	componentRotation.Yaw += -value * rotationVelocity * GetWorld()->GetDeltaSeconds();
	componentRotation.Yaw = FMath::Clamp(componentRotation.Yaw, minAngleRotation, maxAngleRotation);
	SpringArm->SetWorldRotation(componentRotation);

	float armLength = FMath::Clamp(SpringArm->TargetArmLength + value * rotationVelocity, initialArmLength - armLengthVariation, initialArmLength + armLengthVariation);
	SpringArm->TargetArmLength = armLength;
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

	FVector BoostVelocity = GetActorUpVector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
	fastBoostForceCounter = 0;
}

void AMyPlayerFly::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AMyProjectile* projectile = Cast<AMyProjectile>(OtherActor);

	if (projectile != nullptr && isAlive)
	{
		if (projectile->ProjectileType == ECustom::Type::Friendly)
		{
			Health(projectile->HealthAndDamage);
			AddItem();
		}
		else if (projectile->ProjectileType == ECustom::Type::Hostile)
		{
			Damage(projectile->HealthAndDamage);
		}
	}
}

//void AMyPlayerFly::OnActorBump(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
//{
//}
