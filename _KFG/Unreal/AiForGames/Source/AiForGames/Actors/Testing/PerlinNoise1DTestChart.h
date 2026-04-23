// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TestChart.h"
#include "AiForGames/Utils/Random/PerlinNoise1D.h"
#include "GameFramework/Actor.h"
#include "PerlinNoise1DTestChart.generated.h"

UCLASS()
class AIFORGAMES_API APerlinNoise1DTestChart : public ATestChart
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	int octaves = 5;
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	float min = 0;
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	float max = 100;
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	float slopeFactor = 8;
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	float persistence = 0.7;
	UPROPERTY(EditAnywhere, Category="PerlinNoise")
	float step = 0.003;

protected:

private:


public:
	APerlinNoise1DTestChart()
	{
		PrimaryActorTick.bCanEverTick = false;
	}
	
	UFUNCTION(CallInEditor)
	void showNew()
	{
		values.Empty();
		PerlinNoise1D perlinNoise = PerlinNoise1D(octaves, min, max, slopeFactor, persistence);
		for (float t = 0; t <= 1.f; t += step)
		{
			values.Add(perlinNoise.getNextValue(step));
		}
		ShowChart();
	}

protected:
	virtual void BeginPlay() override
	{
		Super::BeginPlay();
		showNew();
	}

private:
};
