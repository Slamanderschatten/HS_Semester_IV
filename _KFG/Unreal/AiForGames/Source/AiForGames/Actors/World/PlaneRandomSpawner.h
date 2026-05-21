#pragma once


#include "CoreMinimal.h"
#include "AiForGames/Actors/NavGraph/NavGraph.h"
#include "GameFramework/Actor.h"
#include "Structs/FSpawnEntry.h"
#include "PlaneRandomSpawner.generated.h"

UCLASS()
class AIFORGAMES_API APlaneRandomSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Spawning")
	UStaticMeshComponent* groundPlane;
	UPROPERTY(EditAnywhere, Category="Spawning")
	FVector distanceFromBorder;
	UPROPERTY(EditAnywhere, Category="Spawning")
	float distanceToNeighbour;
	UPROPERTY(EditAnywhere, Category="Spawning")
	TArray<FSpawnEntry> objectsToSpawn;
	UPROPERTY(EditAnywhere, Category="NavGraph")
	TArray<ANavGraphSpot*> graphSpots;
	
protected:
	
private:
	TArray<AActor*> spawnedActors = TArray<AActor*>();
	NavGraph navGraph;
	
	
	
	
	
	
	
protected:
	virtual void BeginPlay() override;
	
public:
	
	APlaneRandomSpawner();
	
	void Spawn();
	void Clear();
	TArray<AActor*>& GetSpawnedActors();
	
	
};
