#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

UENUM(BlueprintType)
namespace ECustom
{
	enum Type
	{
		Friendly,
		Neutral,
		Hostile,
	};
}

UCLASS()
class UFO_API AMyProjectile : public AActor
{
	GENERATED_BODY()

public:
	AMyProjectile();
protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// declare our float variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UDirectionalGravity* DirectionalGravity;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Multiplier;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector Direction = FVector::ForwardVector;

	UPROPERTY(EditAnywhere, Category = ProjectileType)
		TEnumAsByte<ECustom::Type> ProjectileType = ECustom::Type::Neutral;

	UPROPERTY(EditAnywhere, Category = ProjectileType)
		float HealthAndDamage = 0;
};
