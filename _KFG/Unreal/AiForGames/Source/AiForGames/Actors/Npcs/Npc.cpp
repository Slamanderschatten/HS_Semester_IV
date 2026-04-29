


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
	knowledge = FindComponentByClass<UAIKnowledge>();
	GetComponents<UAIActivatable>(activatables);
	consideration = FindComponentByClass<UAIConsideration>();
	reasoner = FindComponentByClass<UAIReasoner>();
	
	for (UAIActivatable* activatable : activatables)
		activatable->SetKnowledge(knowledge);
	reasoner->SetActivatables(&activatables);
	reasoner->SetConsideration(consideration);
	
}

void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/********************************* getter / setter ****************************************/


UAIKnowledge& ANpc::Knowledge() const
{
	return *knowledge;
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

