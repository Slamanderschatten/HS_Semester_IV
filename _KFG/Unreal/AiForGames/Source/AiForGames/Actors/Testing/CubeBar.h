// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeBar.generated.h"

UCLASS()
class AIFORGAMES_API ACubeBar : public AActor
{
	GENERATED_BODY()

public:

protected:

private:


public:
	ACubeBar()
	{
		UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		RootComponent = Mesh;

		static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
			TEXT("/Engine/BasicShapes/Cube.Cube")
		);

		if (CubeMesh.Succeeded())
		{
			Mesh->SetStaticMesh(CubeMesh.Object);
		}
	}

protected:

private:
};
