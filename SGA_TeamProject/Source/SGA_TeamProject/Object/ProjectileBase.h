// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class SGA_TEAMPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ProjectileFire(FVector Start, FVector direction);
	UFUNCTION(BlueprintCallable)
	void FireDirection(const FVector& direction);

	UFUNCTION()
	virtual void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);

	void SetOwner(class ACharacterBase* owner);
	void SetDamage(int32 dmg) { _damage = dmg; }

	void Activate();
	void Deactivate();

	void SetStartPos(FVector start);
	bool CheckDistance();
	void MeshRotating(float deltaTime);
protected:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _loc;*/

	UPROPERTY()
	class ACharacterBase* _owner;

	int32 _damage = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collider, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _sceneComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collider, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* _collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* _projectileComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float _maxDistance=1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	FRotator _rotating=FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float _rotateSpeed=1.0f;

	FVector _startPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _mesh;

	bool _bisFire = false;

};
