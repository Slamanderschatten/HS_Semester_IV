


#include "Npc.h"


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
	GetComponents<UAIKnowledge>(knowledges);
	GetComponents<UAIActivatable>(activatables);
	consideration = FindComponentByClass<UAIConsideration>();
	reasoner = FindComponentByClass<UAIReasoner>();
	
	reasoner->SetActivatables(&activatables);
	reasoner->SetConsideration(consideration);
	
}

void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/********************************* getter / setter ****************************************/


TArray<UAIKnowledge*>& ANpc::Knowledges()
{
	return knowledges;
}


TArray<UAIActivatable*>& ANpc::Activatables()
{
	return activatables;
}


UAIConsideration& ANpc::Considerations() const
{
	return *consideration;
}


UAIReasoner& ANpc::Reasoner() const
{
	return *reasoner;
}

