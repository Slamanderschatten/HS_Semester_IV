// Copyright © Slamanderschatten. All rights reserved.


#include "AIComponent.h"


UAIComponent::UAIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAIComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

