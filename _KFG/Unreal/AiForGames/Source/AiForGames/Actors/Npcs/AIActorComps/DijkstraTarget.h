// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Flocking.h"
#include "NpcActivatable.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "Components/ActorComponent.h"
#include "DijkstraTarget.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UDijkstraTarget : public UFlocking
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="NavGraph")
	float targetTolerance;

protected:
	UPROPERTY()
	ANavGraphSpot* originSpot;

private:


public:
	virtual void BeginPlay() override;
	virtual void SetTarget(AActor* target) override;

protected:
	virtual void AutoGetTarget() override;

private:
};
