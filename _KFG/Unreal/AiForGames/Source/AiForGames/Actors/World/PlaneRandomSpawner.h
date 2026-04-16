#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/FSpawnEntry.h"
#include "PlaneRandomSpawner.generated.h"

UCLASS()
class AIFORGAMES_API APlaneRandomSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Spawning")
	AActor* spawnPlane;
	UPROPERTY(EditAnywhere, Category="Spawning")
	TArray<FSpawnEntry> objectsToSpawn;
	
	
	
	
	
	
	
protected:
	virtual void BeginPlay() override;
	
public:
	
	APlaneRandomSpawner();
	
	void Spawn();
	
};
