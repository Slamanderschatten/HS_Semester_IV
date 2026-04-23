// Copyright © Slamanderschatten. All rights reserved.


#include "TestChart.h"

#include "CubeBar.h"


ATestChart::ATestChart()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestChart::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATestChart::ShowChart()
{
	while (chartBars.Num() > values.Num())
		chartBars.Pop()->Destroy();
	while (chartBars.Num() < values.Num())
	{
		FActorSpawnParameters spawnParams;

		FVector pos = GetActorLocation() + FVector(0, (chartBars.Num() + 0.5f) * width * 100, 0);

		ACubeBar* bar = GetWorld()->SpawnActor<ACubeBar>(
			ACubeBar::StaticClass(),
			pos,
			FRotator::ZeroRotator,
			spawnParams
		);

		chartBars.Add(bar);
	}
	for (int i = 0; i < values.Num(); i++)
		chartBars[i]->SetActorRelativeScale3D(FVector(width, width, values[i]*heightMultiplier));
}







