// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class SGA_TEAMPROJECT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void PostInitializeComponents()override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned

public:
	// Called every frame

	UFUNCTION()
	void Move(const  FInputActionValue& value);
	UFUNCTION()
	void Look(const  FInputActionValue& value);
	UFUNCTION()
	void TryJump(const  FInputActionValue& value);
	UFUNCTION()
	void Attack(const  FInputActionValue& value);


	UFUNCTION()
	void DropItemByKey(const  FInputActionValue& value);
	UFUNCTION()
	void InvenOpen(const  FInputActionValue& value);

	UFUNCTION()
	void NPCInteract(const  FInputActionValue& value);

	UFUNCTION()
	void DropItemByClick();

	void AddItem(class AItem* item);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _moveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _lookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _jumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _attackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _itemDropAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _invenAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* _NPCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> _invenWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* _invenWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UInvenComponent* _invenComponent;


	bool _isInvenOpen = false;
	
};
