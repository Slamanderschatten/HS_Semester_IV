// Copyright © Slamanderschatten. All rights reserved.


#include "GameM.h"

#include <queue>

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
	SetMouseNearestGraphSpot();
}


void AGameM::SetMouseNearestGraphSpot()
{
	ANavGraphSpot* nearestSpot = GetNearestSpot(npcTarget->GetActorLocation());
	if (nearestSpot != targetNearestSpot)
	{
		targetNearestSpot = nearestSpot;
		ActualizeDijkstraTree();
	}
}


ANavGraphSpot* AGameM::GetNearestSpot(const FVector& pos)
{
	ANavGraphSpot* nearestSpot = nullptr;
	float nearestSpotDistance = 100000;
	for (ANavGraphSpot* spot : navGraphSpots)
	{
		float dist = FVector::Dist(spot->GetActorLocation(), pos);
		if (dist < nearestSpotDistance)
		{
			nearestSpot = spot;
			nearestSpotDistance = dist;
		}
	}
	return nearestSpot;
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

	if (!targetNearestSpot)
	{
		return;
	}

	std::unordered_map<ANavGraphSpot*, float> distances;

	for (ANavGraphSpot* spot : navGraphSpots)
	{
		distances[spot] = FLT_MAX;
	}

	using QueueEntry = std::pair<float, ANavGraphSpot*>;

	auto Compare = [](const QueueEntry& a, const QueueEntry& b)
	{
		return a.first > b.first;
	};

	std::priority_queue<
		QueueEntry,
		std::vector<QueueEntry>,
		decltype(Compare)
	> queue(Compare);

	distances[targetNearestSpot] = 0.0f;
	queue.push({0.0f, targetNearestSpot});

	while (!queue.empty())
	{
		auto [currentDistance, current] = queue.top();
		queue.pop();

		if (currentDistance > distances[current])
		{
			continue;
		}

		for (ANavGraphSpot* neighbour : current->neighbours)
		{
			if (!neighbour)
			{
				continue;
			}

			float edgeCost = FVector::Distance(
				current->GetActorLocation(),
				neighbour->GetActorLocation());

			float newDistance = currentDistance + edgeCost;

			if (newDistance < distances[neighbour])
			{
				distances[neighbour] = newDistance;

				// WICHTIG:
				// neighbour -> current
				// current liegt näher am Ziel
				dijkstraTreeMap[neighbour] = current;

				queue.push({newDistance, neighbour});
			}
		}
	}
}


ANavGraphSpot* AGameM::GetNextDijkstraSpot(ANavGraphSpot* startSpot) const
{
	auto it = dijkstraTreeMap.find(startSpot);
	if (it != dijkstraTreeMap.end())
		return it->second;
	return startSpot;
}


ANavGraphSpot* AGameM::GetDijkstraTargetSpot() const
{
	return targetNearestSpot;
}



