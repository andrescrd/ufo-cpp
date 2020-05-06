#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/Damagable.h"
#include "Interfaces/Abducible.h"
#include "GameFramework\Character.h"

AMyPlayer::AMyPlayer()
{
	//PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(GetRootComponent());
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1);
	Body->SetConstraintMode(EDOFMode::XYPlane);

	AbductionZone = CreateDefaultSubobject<UCapsuleComponent>("Abduction Zone Collider");
	AbductionZone->SetCapsuleSize(40, 100);
	AbductionZone->SetupAttachment(Body);
	// camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	// camera->SetupAttachment(body);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	AbductionZone->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneBeginOverlap);
	AbductionZone->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnAbductionZoneEndOverlap);
}

void AMyPlayer::Tick(float DeltaTime)
{

}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveVertical);
	playerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::Rotate);

	playerInputComponent->BindAction("Fast", IE_Pressed, this, &AMyPlayer::StartFastBoost);
	// PlayerInputComponent->BindAction("Fast", IE_Released, this, &AMyPlayer::StopFastBoost);

	playerInputComponent->BindAction("Abduction", IE_Pressed, this, &AMyPlayer::StartAbduction);
	playerInputComponent->BindAction("Abduction", IE_Released, this, &AMyPlayer::StopAbduction);

	playerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPlayer::StartFire);
}

void AMyPlayer::MoveVertical(float value)
{
	FVector Movement = FVector(value * velocity * GetWorld()->GetDeltaSeconds(), 0, 0);
	AddActorLocalOffset(Movement, true);
}

void AMyPlayer::Rotate(float value)
{
	FRotator Rotation = FRotator(0, value * rotationVelocity * GetWorld()->GetDeltaSeconds(), 0);
	AddActorLocalRotation(Rotation);
}

void AMyPlayer::StartFastBoost()
{
	if (!hasFastBoost)
	{
		GetWorldTimerManager().SetTimer(fastBoostTimerHandle, this, &AMyPlayer::FastBoostTimer, 0.3, true);
		GetWorldTimerManager().SetTimer(stopFastBoostTimerHandle, this, &AMyPlayer::StopFastBoost, fastBoostDuration, false);
	}
}

void AMyPlayer::FastBoostTimer()
{
	hasFastBoost = true;
	FVector BoostVelocity = GetActorRotation().Vector() * velocity * fastBoostForce * GetWorld()->GetDeltaSeconds();
	Body->SetPhysicsLinearVelocity(BoostVelocity, true);
}

void AMyPlayer::StopFastBoost()
{
	hasFastBoost = false;
	GetWorldTimerManager().ClearTimer(fastBoostTimerHandle);
}

void AMyPlayer::StartAbduction()
{
	abductionOn = true;
	GetWorldTimerManager().SetTimer(abductionTimerHandle, this, &AMyPlayer::AbductionTimer, 0.1, true);
}

void AMyPlayer::AbductionTimer()
{
	if (abductionOn)
	{
		TArray<AActor*> overlappedActors;
		AbductionZone->GetOverlappingActors(overlappedActors);

		if (overlappedActors.Num() > 0)
		{
			abductible = nullptr;

			for (int i = 0; i < overlappedActors.Num(); i++)
			{
				abductible = Cast<IAbducible>(overlappedActors[i]);

				if (abductible)
				{
					break;
				}
			}

			if (abductible != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("overlapped %s"), *abductible->_getUObject()->GetName());
				abductible->StartAbductionMode();
				AActor* currentActor = Cast<AActor>(abductible);
				FVector location = currentActor->GetActorLocation();
				location.Z += abductionForce * GetWorld()->GetDeltaSeconds();
				currentActor->SetActorLocation(location, true);

				DrawDebugLine(GetWorld(),
					GetActorLocation(),
					location,
					FColor::Orange, false, 3);
			}
		}
	}
}

void AMyPlayer::StopAbduction()
{
	abductionOn = false;
	GetWorldTimerManager().ClearTimer(abductionTimerHandle);

	if (abductible)
	{
		abductible->DisableAbductionMode();
		abductible = nullptr;
	}
}

void AMyPlayer::StartFire()
{
	Fire(10, 500);
}

void AMyPlayer::Fire(int fireAmount, float fireRadio)
{
	for (int i = 0; i < fireAmount; i++)
	{
		FHitResult hitResult;

		FVector shootRadio = FVector(FMath::RandRange(-fireRadio, fireRadio), FMath::RandRange(-fireRadio, fireRadio), FMath::RandRange(-fireRadio, fireRadio));
		FVector dest = GetActorLocation() + GetActorRotation().Vector() * shootForce + shootRadio;

		GetWorld()->LineTraceSingleByChannel(
			hitResult,
			GetActorLocation(),
			dest,
			ECollisionChannel::ECC_Destructible);

		DrawDebugLine(GetWorld(),
			GetActorLocation(),
			dest,
			FColor::Red, false, 3);

		if (hitResult.GetActor())
		{
			//UE_LOG(LogTemp, Warning, TEXT("Damaged: %s"), hitResult.GetActor()->GetName());
			IDamagable* damagable = Cast<IDamagable>(hitResult.GetActor());

			if (damagable)
			{
				damagable->Damage(damage);
			}
		}
	}
}

void AMyPlayer::OnAbductionZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (abductionOn)
	{
		IAbducible* abducibleObject = Cast<IAbducible>(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("overlapped %s"), *abducibleObject->_getUObject()->GetName());

		if (abducibleObject)
		{
			abducibleObject->StartAbduction();
		}
	}
	else
	{
		IAbducible* abducibleObject = Cast<IAbducible>(OtherActor);

		if (abducibleObject)
		{
			abducibleObject->AbductedFail();
		}
	}*/
}

void AMyPlayer::OnAbductionZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IAbducible* abducibleObject = Cast<IAbducible>(OtherActor);	
	if (abductible && abducibleObject)
	{
		abductible->DisableAbductionMode();
		abductible = nullptr;
	}	
}