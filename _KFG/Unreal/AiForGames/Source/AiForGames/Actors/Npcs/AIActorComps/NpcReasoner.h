// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIReasoner.h"
#include "AiForGames/Actors/Manager/Enums/NpcTargetInteraction.h"
#include "Components/ActorComponent.h"
#include "NpcReasoner.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UNpcReasoner : public UAIReasoner
{
	GENERATED_BODY()

public:

protected:

private:
	
	AActor* npcTarget;
	UNpcTargetInteraction npcTargetInteraction;


public:
	UNpcReasoner();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Process() override;

protected:

private:
};
