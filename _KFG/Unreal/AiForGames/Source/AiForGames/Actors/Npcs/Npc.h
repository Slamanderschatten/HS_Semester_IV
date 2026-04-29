

#pragma once

#include "CoreMinimal.h"
#include "AiForGames/Actors/AI/ActorComps/AIActivatable.h"
#include "AiForGames/Actors/AI/ActorComps/AIConsideration.h"
#include "AiForGames/Actors/AI/ActorComps/AIKnowledge.h"
#include "AiForGames/Actors/AI/ActorComps/AIReasoner.h"
#include "GameFramework/Actor.h"
#include "Npc.generated.h"

UCLASS()
class AIFORGAMES_API ANpc : public AActor
{
	GENERATED_BODY()
	
public:
	
protected:
	
private:
	UAIKnowledge* knowledge;
	TArray<UAIActivatable*> activatables;
	UAIConsideration* consideration;
	UAIReasoner* reasoner;
	
	
	
	
	
	

public:
	ANpc();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	UAIKnowledge& Knowledge() const;
	TArray<UAIActivatable*>& Activatables();
	UAIConsideration& Considerations() const;
	UAIReasoner& Reasoner() const;

protected:
	virtual void BeginPlay() override;

private:
	
};
