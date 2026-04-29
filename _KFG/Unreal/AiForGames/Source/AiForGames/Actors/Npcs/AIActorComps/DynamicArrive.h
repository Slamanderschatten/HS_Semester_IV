// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "Components/ActorComponent.h"
#include "DynamicArrive.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UDynamicArrive : public UAIActivatable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Velocity")
	float maxAcceleration = 100;
	UPROPERTY(EditAnywhere, Category="Velocity")
	float maxVelocity = 100;
	UPROPERTY(EditAnywhere, Category="Velocity")
	float targetRadius = 5;
	UPROPERTY(EditAnywhere, Category="Velocity")
	float breakFactor = 0.95;

protected:
	FVector linearVelocity = FVector::ZeroVector;
	AActor* origin;

private:


public:
	UDynamicArrive();
	void SetTarget(AActor* seeker);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:

private:
	void ActualizePosition(float deltaTime);
};
