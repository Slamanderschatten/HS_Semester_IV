// Copyright © Slamanderschatten. All rights reserved.


#include "NpcConsideration.h"


// Sets default values for this component's properties
UNpcConsideration::UNpcConsideration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNpcConsideration::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNpcConsideration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNpcConsideration::SetNpc(ANpc* npcActor)
{
	npc = npcActor;
}

