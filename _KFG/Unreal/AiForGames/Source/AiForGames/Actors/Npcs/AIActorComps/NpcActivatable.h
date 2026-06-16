// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NpcKnowledge.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "Components/ActorComponent.h"
#include "NpcActivatable.generated.h"


class ANpc;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UNpcActivatable : public UAIActivatable
{
	GENERATED_BODY()

public:

protected:
	ANpc* npc;

private:


public:
	void SetNpc(ANpc* npcActor);

protected:

private:
};
