// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataTable.h"
#include "../Character/PlayerCharacter.h"
#include "../CGameInstance.h"
#include "ItemBase.generated.h"

UCLASS(Abstract)
class SGA_TEAMPROJECT_API AItemBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();
	void Deactivate();

	bool IsActive() { return _isActive; }
	void SetActive(bool isActive) { _isActive = isActive; };

	virtual void UseItem(class APlayerCharacter*) PURE_VIRTUAL(AItemBase::UseItem, );

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);

	const FItemData& GetData() { return _itemData; }
	void SetData(const FItemData& itemData);

private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* _mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* _collider;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemData _itemData;

	bool _isActive;
	bool _dataIsSet = false;
};
