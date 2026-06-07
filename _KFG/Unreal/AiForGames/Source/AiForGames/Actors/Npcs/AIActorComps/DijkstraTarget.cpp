// Copyright © Slamanderschatten. All rights reserved.


#include "DijkstraTarget.h"

#include "AiForGames/Actors/Npcs/Npc.h"


void UDijkstraTarget::BeginPlay()
{
	Super::BeginPlay();
}

void UDijkstraTarget::SetTarget(AActor* target)
{
	Super::SetTarget(target);
	originSpot = Cast<ANavGraphSpot>(origin);
}

void UDijkstraTarget::AutoGetTarget()
{
	if (origin == nullptr)
		SetTarget(npc->Knowledge().GetGameManager().GetNearestSpot(GetOwner()->GetActorLocation()));
	if (FVector::Dist(GetOwner()->GetActorLocation(), originSpot->GetActorLocation()) < targetTolerance + originSpot->spotRadius)
		SetTarget(npc->Knowledge().GetNextDijkstraSpot(originSpot));
}

