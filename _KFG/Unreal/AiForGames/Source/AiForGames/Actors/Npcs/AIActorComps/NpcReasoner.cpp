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
	ENpcTargetInteraction interaction = AGameManager::I()->GetNpcTargetInteraction();
	if (target == npcTarget && interaction == npcTargetInteraction)
		return;
	
	switch (interaction)
	{
	case ENpcTargetInteraction::FleeKinematic:
		break;
	case ENpcTargetInteraction::FleeDynamic:
		break;
	case ENpcTargetInteraction::SeekKinematic:
		break;
	case ENpcTargetInteraction::SeekDynamic:
		break;
	}
}




