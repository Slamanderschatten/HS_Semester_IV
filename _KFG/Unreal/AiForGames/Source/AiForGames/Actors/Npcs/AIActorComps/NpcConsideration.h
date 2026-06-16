// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIConsideration.h"
#include "Components/ActorComponent.h"
#include "NpcConsideration.generated.h"


class ANpc;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UNpcConsideration : public UAIConsideration
{
	GENERATED_BODY()

public:

protected:
	ANpc* npc;

private:


public:
	UNpcConsideration();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void SetNpc(ANpc* npcActor);

protected:

private:
};
