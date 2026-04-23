// Copyright © Slamanderschatten. All rights reserved.


#include "NpcReasoner.h"

#include "AiForGames/Actors/Manager/GameManager.h"


UNpcReasoner::UNpcReasoner()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UNpcReasoner::BeginPlay()
{
	Super::BeginPlay();

	
}


void UNpcReasoner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UNpcReasoner::Process()
{
	AActor* target = AGameManager::I()->GetNpcTarget();
	UNpcTargetInteraction interaction = AGameManager::I()->GetNpcTargetInteraction();
	if (target == npcTarget && interaction == npcTargetInteraction)
		return;
	
	switch (interaction)
	{
	case UNpcTargetInteraction::FleeKinematic:
		break;
	case UNpcTargetInteraction::FleeDynamic:
		break;
	case UNpcTargetInteraction::SeekKinematic:
		break;
	case UNpcTargetInteraction::SeekDynamic:
		break;
	}
}




