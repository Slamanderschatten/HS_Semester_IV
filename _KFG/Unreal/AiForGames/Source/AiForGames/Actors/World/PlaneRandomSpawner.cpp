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
			GetWorld()->SpawnActor<AActor>(entry.actorClass, randomPosition, FRotator::ZeroRotator, spawnParams);
		}
	}
	
}

