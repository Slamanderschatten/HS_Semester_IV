// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIKnowledge.h"
#include "AiForGames/Actors/Manager/GameM.h"
#include "AiForGames/Actors/Manager/Enums/NpcTargetInteraction.h"
#include "Components/ActorComponent.h"
#include "NpcKnowledge.generated.h"


class AGameManager;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UNpcKnowledge : public UAIKnowledge
{
	GENERATED_BODY()

public:

protected:
	AGameM* gameManager;

private:


public:
	UNpcKnowledge();
	virtual void BeginPlay() override;
	ENpcTargetInteraction GetNpcTargetInteraction() const;
	AActor* GetNpcTarget() const;

protected:

private:
};
