#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FSpawnEntry.generated.h"

USTRUCT(BlueprintType)
struct FSpawnEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> actorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 spawnCount;
};
