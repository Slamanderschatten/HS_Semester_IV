#include "PlaneRandomSpawner.h"

#include "Kismet/KismetMathLibrary.h"


APlaneRandomSpawner::APlaneRandomSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	groundPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground"));
	RootComponent = groundPlane;
}


void APlaneRandomSpawner::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}


void APlaneRandomSpawner::Spawn()
{
	Clear();
	
	if (objectsToSpawn.Num() == 0)
		return;
	
	FVector planeScale = groundPlane->GetComponentScale();
	FVector boundingBox = FVector(
		planeScale.X/2*100 - distanceFromBorder.X, 
		planeScale.Y/2*100 - distanceFromBorder.Y, 
		0);
	for(FSpawnEntry entry : objectsToSpawn)
	{
		if (entry.actorClass == nullptr)
			continue;
		
		for (int i = 0; i < entry.spawnCount; i++)
		{
			FActorSpawnParameters spawnParams;
			FVector randomPosition = UKismetMathLibrary::RandomPointInBoundingBox(
				GetActorLocation(),
				boundingBox);
			FRotator randomRotation = FRotator(0, FMath::FRandRange(0.f, 360.f), 0);
			AActor* newActor = GetWorld()->SpawnActor<AActor>(
				entry.actorClass, FVector::Zero(), randomRotation, spawnParams
				);
			
			bool newPos;
			int errorCount = 0;
			do 
			{
				newPos = false;
				randomPosition = UKismetMathLibrary::RandomPointInBoundingBox(
					GetActorLocation(),
					boundingBox);
				newActor->SetActorLocation(randomPosition);

				for (AActor* otherActor : spawnedActors)
				{
					if (otherActor->GetDistanceTo(newActor) < distanceToNeighbour)
					{
						newPos = true;
						break;
					}
				}
				
				if (++errorCount > 50)
					return;
			} while(newPos);
			
			spawnedActors.Add(newActor);
		}
	}	
}


void APlaneRandomSpawner::Clear()
{
	for (AActor* actor : spawnedActors)
	{
		if (actor != nullptr)
			actor->Destroy();
	}
	spawnedActors.Empty();
}

