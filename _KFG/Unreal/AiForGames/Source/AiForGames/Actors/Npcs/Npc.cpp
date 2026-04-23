


#include "Npc.h"


ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ANpc::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetOwner()->GetComponents<UAIKnowledge>(knowledges);
	GetOwner()->GetComponents<UAIActivatable>(activatables);
	consideration = GetOwner()->FindComponentByClass<UAIConsideration>();
	reasoner = GetOwner()->FindComponentByClass<UAIReasoner>();
	
	reasoner->SetActivatables(&activatables);
	reasoner->SetConsideration(consideration);
}


void ANpc::BeginPlay()
{
	Super::BeginPlay();
	
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

