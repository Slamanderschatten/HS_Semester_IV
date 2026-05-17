

#pragma once

#include "CoreMinimal.h"
#include "AIActorComps/NpcActivatable.h"
#include "AIActorComps/NpcConsideration.h"
#include "AIActorComps/NpcKnowledge.h"
#include "AIActorComps/NpcReasoner.h"
#include "GameFramework/Actor.h"
#include "Npc.generated.h"

UCLASS()
class AIFORGAMES_API ANpc : public AActor
{
	GENERATED_BODY()
	
public:
	
protected:
	
private:
	UNpcKnowledge* knowledge;
	TArray<UNpcActivatable*> activatables;
	TArray<UAIActivatable*> activatablesAI;
	UNpcConsideration* consideration;
	UNpcReasoner* reasoner;
	
	
	
	
	
	

public:
	ANpc();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	UNpcKnowledge& Knowledge() const;
	TArray<UNpcActivatable*>& Activatables();
	UNpcConsideration& Considerations() const;
	UNpcReasoner& Reasoner() const;

protected:
	virtual void BeginPlay() override;

private:
	
};
