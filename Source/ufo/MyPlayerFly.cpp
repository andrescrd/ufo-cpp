#include "MyPlayerFly.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
AMyPlayerFly::AMyPlayerFly()
{
	//PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetSimulatePhysics(true);
	Body->SetEnableGravity(false);
	Body->SetConstraintMode(EDOFMode::XZPlane);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Body;
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 3000.0f;

	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	initialArmLength = SpringArm->TargetArmLength;
}

// Called when the game starts or when spawned
void AMyPlayerFly::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyPlayerFly::OnOverlap);
}

//// Called every frame
//void AMyPlayerFly::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

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
	AddActorLocalOffset(movment, true);
}

void AMyPlayerFly::Rotate(float value)
{
	FRotator componentRotation = SpringArm->GetComponentRotation();
	componentRotation.Yaw += -value * rotationVelocity * GetWorld()->GetDeltaSeconds();
	componentRotation.Yaw = FMath::Clamp(componentRotation.Yaw, minAngleRotation, maxAngleRotation);
	SpringArm->SetWorldRotation(componentRotation);

	float armLength = FMath::Clamp(SpringArm->TargetArmLength  + value * rotationVelocity, initialArmLength - armLengthVariation, initialArmLength + armLengthVariation);
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Overlap: %s"), *OtherActor->GetName()));
}
