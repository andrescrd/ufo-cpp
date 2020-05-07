#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ufo/Interfaces/Damagable.h"
#include "ufo/Interfaces/Healthable.h"
#include "ufo/Interfaces/EnemyAttack.h"
#include "MyEnemy.generated.h"

UCLASS()
class UFO_API AMyEnemy : public ACharacter, public IDamagable, public IHealthable, public IEnemyAttack
{
	GENERATED_BODY()

public:
	AMyEnemy();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere) float life = 100;
	UPROPERTY(EditAnywhere) float maxLife = 100;
	UPROPERTY(EditAnywhere) float damage = 5;
	UPROPERTY(EditAnywhere) TSubclassOf<class AActor> spawnedObject;

	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Damage(float amount);
	virtual	void Health(float amount);
	virtual	void Attack();;
};
