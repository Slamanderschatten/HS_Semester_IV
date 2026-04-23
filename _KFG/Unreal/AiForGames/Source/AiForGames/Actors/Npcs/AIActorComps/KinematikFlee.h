// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "Components/ActorComponent.h"
#include "KinematikFlee.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UKinematikFlee : public UAIActivatable
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category="Velocity")
	float maxVelocity;

protected:

private:
	FVector linearVelocity;
	AActor* origin;


public:
	UKinematikFlee();
	void SetSeeker(AActor* seeker);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:

private:
	void ActualizePosition(float deltaTime) const;
};
