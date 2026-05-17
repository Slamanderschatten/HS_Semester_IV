// Copyright © Slamanderschatten. All rights reserved.


#include "NpcReasoner.h"

#include "DynamicArrive.h"
#include "DynamicFlee.h"
#include "DynamicSeek.h"
#include "KinematicSeek.h"
#include "KinematikFlee.h"
#include "AiForGames/Actors/Npcs/Npc.h"


UNpcReasoner::UNpcReasoner()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UNpcReasoner::BeginPlay()
{
	Super::BeginPlay();

	
}


void UNpcReasoner::SetActivatables(TArray<UAIActivatable*>* activatableList)
{
	Super::SetActivatables(activatableList);
	if (npcTarget == nullptr) npcTarget = npc->Knowledge().GetNpcTarget();
	for (UAIActivatable* activatable : *activatableList)
	{
		if (UDynamicFlee* a = Cast<UDynamicFlee>(activatable))
			a->SetSeeker(npcTarget);
		if (UKinematikFlee* a = Cast<UKinematikFlee>(activatable))
			a->SetSeeker(npcTarget);
		if (UDynamicSeek* a = Cast<UDynamicSeek>(activatable))
			a->SetTarget(npcTarget);
		if (UKinematicSeek* a = Cast<UKinematicSeek>(activatable))
			a->SetTarget(npcTarget);
		if (UDynamicArrive* a = Cast<UDynamicArrive>(activatable))
			a->SetTarget(npcTarget);
	}
}

void UNpcReasoner::SetNpc(ANpc* npcActor)
{
	npc = npcActor;
}


void UNpcReasoner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Process();
}


void UNpcReasoner::Process()
{
	AActor* target = npc->Knowledge().GetNpcTarget();
	ENpcTargetInteraction interaction = npc->Knowledge().GetNpcTargetInteraction();
	if (target == npcTarget && interaction == npcTargetInteraction)
		return;
	
	npcTargetInteraction = interaction;
	npcTarget = target;
	
	UClass* type = nullptr;
	switch (interaction)
	{
	case ENpcTargetInteraction::FleeKinematic:
		type = UKinematikFlee::StaticClass();
		break;
	case ENpcTargetInteraction::FleeDynamic:
		type = UDynamicFlee::StaticClass();
		break;
	case ENpcTargetInteraction::SeekKinematic:
		type = UKinematicSeek::StaticClass();
		break;
	case ENpcTargetInteraction::SeekDynamic:
		type = UDynamicSeek::StaticClass();
		break;
	case ENpcTargetInteraction::ArriveDynamic:
		type = UDynamicArrive::StaticClass();
		break;
		
	case ENpcTargetInteraction::Non:
		break;
	}
	
	DeactivateActivatable(moveActivatable);
	moveActivatable = ActivateActivatable(type);
	
	
}




