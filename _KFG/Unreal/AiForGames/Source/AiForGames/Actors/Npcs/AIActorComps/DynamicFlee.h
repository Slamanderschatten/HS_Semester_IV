// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "Components/ActorComponent.h"
#include "DynamicFlee.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UDynamicFlee : public UAIActivatable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Velocity")
	float maxAcceleration;
	UPROPERTY(EditAnywhere, Category="Velocity")
	float maxVelocity;

protected:

private:
	FVector linearVelocity = FVector::ZeroVector;
	AActor* origin;


public:
	UDynamicFlee() = default;
	void SetSeeker(AActor* seeker);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:

private:
	void ActualizePosition(float deltaTime);
};
