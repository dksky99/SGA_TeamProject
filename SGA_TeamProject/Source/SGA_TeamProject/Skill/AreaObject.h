// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "AreaObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FFieldEnd);

UCLASS()
class SGA_TEAMPROJECT_API AAreaObject : public AActor
{
	GENERATED_BODY()
public:
	AAreaObject();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Play(FVector pos);

	UFUNCTION()
	void DeActiveEvent();

	void SetScale(float x, float y);

	void Activate();
	void Deactivate();

	FFieldEnd _endEvent;

private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _sceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide", meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* _decalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _areaRadius = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _delayTime = 3.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _runTime = 0.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	bool _bIsPlay = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEffectBase> _effectClass;

	UPROPERTY()
	class AEffectBase* _effect;

};
