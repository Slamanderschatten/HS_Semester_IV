

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ANpc.generated.h"

UCLASS()
class AIFORGAMES_API AANpc : public AActor
{
	GENERATED_BODY()

public:
	AANpc();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
