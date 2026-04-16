#include "PlaneRandomSpawner.h"

#include "Kismet/KismetMathLibrary.h"


APlaneRandomSpawner::APlaneRandomSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}


void APlaneRandomSpawner::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}


void APlaneRandomSpawner::Spawn()
{
	if (objectsToSpawn.Num() == 0 || spawnPlane == nullptr)
		return;
	
	FVector planeScale = spawnPlane->GetActorScale3D();
	for(FSpawnEntry entry : objectsToSpawn)
	{
		if (entry.actorClass == nullptr)
			continue;
		
		FVector randomPosition = UKismetMathLibrary::RandomPointInBoundingBox(
			GetActorLocation(),
			FVector(planeScale.X/2, planeScale.Y/2, 0));
		FActorSpawnParameters spawnParams;
		GetWorld()->SpawnActor<AActor>(entry.actorClass, randomPosition, FRotator::ZeroRotator, spawnParams);
	}
	
}

