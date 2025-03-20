// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageLoggingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAMPROJECT_API UDamageLoggingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageLoggingComponent();

	void Logging(class ACharacterBase* causer, int32 damage);
	class ACharacterBase* GetBestDamageCauser();
	const TMap<class ACharacterBase*, int32>& GetLog();
	TArray<TPair<class ACharacterBase*, int32>> GetValidList();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void EraseLog();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Log", meta = (AllowPrivateAccess = "true"))
	TMap<class ACharacterBase*, int32> _damageLog;
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Reset",meta=(AllowPrivateAccess="true"))
	float resetTime = 20.0f;
	UPROPERTY(VisibleAnywhere)
	float curTime = 0.0f;
};
