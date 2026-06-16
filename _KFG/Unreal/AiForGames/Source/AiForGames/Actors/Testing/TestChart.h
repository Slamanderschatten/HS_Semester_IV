// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestChart.generated.h"

UCLASS(Abstract, Blueprintable)
class AIFORGAMES_API ATestChart : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="ChartVisu")
	float heightMultiplier;
	UPROPERTY(EditAnywhere, Category="ChartVisu")
	float width;
	
protected:
	TArray<float> values;
	
private:
	TArray<AActor*> chartBars;


public:
	ATestChart();

protected:
	virtual void BeginPlay() override;
	void ShowChart();

private:
};
