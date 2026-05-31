// Copyright © Slamanderschatten. All rights reserved.


#include "GameM.h"

#include "HLSLMathAliases.h"
#include "Factories/TextureRenderTargetFactoryNew.h"
#include "Kismet/GameplayStatics.h"


AGameM::AGameM()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AGameM::BeginPlay()
{
	Super::BeginPlay();
	playerController = GetWorld()->GetFirstPlayerController();
	playerController->bShowMouseCursor = true;
	playerController->bEnableMouseOverEvents = true;
	playerController->bEnableClickEvents = true;
	
	TArray<AActor*> navGraphSpotActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavGraphSpot::StaticClass(), navGraphSpotActors);
	for (AActor* actor : navGraphSpotActors)
	{
		ANavGraphSpot* spot = Cast<ANavGraphSpot>(actor);
		navGraphSpots.Add(spot);
		navGraph.addNode(spot);
	}
	for (ANavGraphSpot* spot : navGraphSpots)
	{
		for (ANavGraphSpot* neighbour : spot->neighbours)
			navGraph.addEdgeForSpots(spot, neighbour);
	}
}


AActor* AGameM::GetNpcTarget() const
{
	return npcTarget;
}


ENpcTargetInteraction AGameM::GetNpcTargetInteraction() const
{
	return npcTargetInteraction;
}

bool AGameM::IsFlockingEnabled() const
{
	return enableFlocking;
}

TArray<AActor*> AGameM::GetNpcList() const
{
	return npcGround->GetSpawnedActors();
}

void AGameM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetNpcTargetToMousePos();
}


void AGameM::SetMouseNearestGraphSpot()
{
	ANavGraphSpot* nearestSpot = nullptr;
	float nearestSpotDistance = 100000;
	for (ANavGraphSpot* spot : navGraphSpots)
	{
		float dist = FVector::Dist(spot->GetActorLocation(), npcTarget->GetActorLocation());
		if (dist < nearestSpotDistance)
		{
			nearestSpot = spot;
			nearestSpotDistance = dist;
		}
	}
	if (nearestSpot != targetNearestSpot)
	{
		ActualizeDijkstraTree();
	}
}


void AGameM::SetNpcTargetToMousePos() const
{
	if (npcTarget == nullptr)
		return;
	FVector WorldLocation;
	FVector WorldDirection;

	if (!playerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		return;

	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_GameTraceChannel1
	);

	if (Hit.bBlockingHit)
	{
		npcTarget->SetActorLocation(Hit.ImpactPoint);
	}
}


void AGameM::ActualizeDijkstraTree()
{
	dijkstraTreeMap.clear();
	
	//todo
}


ANavGraphSpot* AGameM::GetNextDijkstraSpot(ANavGraphSpot* startSpot) const
{
	auto it = dijkstraTreeMap.find(startSpot);
	if (it != dijkstraTreeMap.end())
		return it->second;
	return nullptr;
}



