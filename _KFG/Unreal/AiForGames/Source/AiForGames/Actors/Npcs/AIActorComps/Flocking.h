// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DynamicSeek.h"
#include "NpcActivatable.h"
#include "Components/ActorComponent.h"
#include "Flocking.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UFlocking : public UDynamicSeek
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Flocking")
	float radiusOfInfluence;
	UPROPERTY(EditAnywhere, Category="Flocking")
	float cohesionMaxForce = 100;
	UPROPERTY(EditAnywhere, Category="Flocking")
	float radiusOfCohesion;
	UPROPERTY(EditAnywhere, Category="Flocking")
	float separationMaxForce = 100;
	UPROPERTY(EditAnywhere, Category="Flocking")
	float radiusOfSeparation;

protected:

private:


public:
	UFlocking();

protected:

private:
	FVector FlockingForce(FVector acceleration) const;
	virtual void ActualizePosition(float deltaT) override;
};
