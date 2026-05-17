


#include "Npc.h"

#include "AIActorComps/NpcActivatable.h"
#include "AIActorComps/NpcConsideration.h"
#include "AIActorComps/NpcKnowledge.h"
#include "AIActorComps/NpcReasoner.h"


class UNpcActivatable;

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ANpc::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ANpc::BeginPlay()
{
	Super::BeginPlay();
	knowledge = FindComponentByClass<UNpcKnowledge>();
	GetComponents<UNpcActivatable>(activatables);
	GetComponents<UAIActivatable>(activatablesAI);
	consideration = FindComponentByClass<UNpcConsideration>();
	reasoner = FindComponentByClass<UNpcReasoner>();
	
	for (UNpcActivatable* activatable : activatables)
		activatable->SetNpc(this);
	reasoner->SetNpc(this);
	reasoner->SetActivatables(&activatablesAI);
	consideration->SetNpc(this);
	
}

void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/********************************* getter / setter ****************************************/


UNpcKnowledge& ANpc::Knowledge() const
{
	return *knowledge;
}


TArray<UNpcActivatable*>& ANpc::Activatables()
{
	return activatables;
}


UNpcConsideration& ANpc::Considerations() const
{
	return *consideration;
}


UNpcReasoner& ANpc::Reasoner() const
{
	return *reasoner;
}

