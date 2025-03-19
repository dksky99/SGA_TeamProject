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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _loc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* _projectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _mesh;

};
