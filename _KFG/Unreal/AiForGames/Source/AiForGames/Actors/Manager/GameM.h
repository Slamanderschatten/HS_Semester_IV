// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include <unordered_map>

#include "CoreMinimal.h"
#include "AiForGames/Actors/World/PlaneRandomSpawner.h"
#include "Enums/NpcTargetInteraction.h"
#include "GameFramework/Actor.h"
#include "GameM.generated.h"

UCLASS()
class AIFORGAMES_API AGameM : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Npcs")
	AActor* npcTarget = nullptr;
	UPROPERTY(EditAnywhere, Category="Npcs")
	APlaneRandomSpawner* npcGround = nullptr;
	UPROPERTY(EditAnywhere, Category="Npcs")
	ENpcTargetInteraction npcTargetInteraction = ENpcTargetInteraction::Non;
	UPROPERTY(EditAnywhere, Category="Npcs")
	bool enableFlocking = false;

protected:
	APlayerController* playerController;
	NavGraph navGraph;
	TArray<ANavGraphSpot*> navGraphSpots;
	ANavGraphSpot* targetNearestSpot;
	std::unordered_map<ANavGraphSpot*, ANavGraphSpot*> dijkstraTreeMap;
	

private:


public:
	AGameM();
	virtual void Tick(float DeltaTime) override;
	void SetMouseNearestGraphSpot();
	AActor* GetNpcTarget() const;
	ENpcTargetInteraction GetNpcTargetInteraction() const;
	bool IsFlockingEnabled() const;
	TArray<AActor*> GetNpcList() const;
	ANavGraphSpot* GetNextDijkstraSpot(ANavGraphSpot* startSpot) const;

protected:
	virtual void BeginPlay() override;

private:
	void SetNpcTargetToMousePos() const;
	void ActualizeDijkstraTree();
};
