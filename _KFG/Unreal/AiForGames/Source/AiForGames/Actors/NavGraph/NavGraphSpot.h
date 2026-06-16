// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavGraphSpot.generated.h"

UCLASS()
class AIFORGAMES_API ANavGraphSpot : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Spot")
	TArray<ANavGraphSpot*> neighbours;
	UPROPERTY(EditAnywhere, Category="Spot")
	float spotRadius = 0;

public:

protected:

public:
};
