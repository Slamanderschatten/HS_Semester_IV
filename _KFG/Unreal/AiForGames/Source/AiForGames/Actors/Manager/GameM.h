// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
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
	ENpcTargetInteraction npcTargetInteraction = ENpcTargetInteraction::Non;

protected:

private:


public:
	AActor* GetNpcTarget() const;
	ENpcTargetInteraction GetNpcTargetInteraction() const;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	void SetNpcTargetToMousePos();
};
