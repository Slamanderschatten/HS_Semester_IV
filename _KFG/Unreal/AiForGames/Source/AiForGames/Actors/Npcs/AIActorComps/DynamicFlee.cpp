// Copyright © Slamanderschatten. All rights reserved.


#include "DynamicFlee.h"





void UDynamicFlee::SetSeeker(AActor* seeker)
{
	origin = seeker;
}


// Called every frame
void UDynamicFlee::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActualizePosition(DeltaTime);
}


void UDynamicFlee::ActualizePosition(float deltaT)
{
	FVector acceleration = GetOwner()->GetActorForwardVector() - origin->GetActorLocation();;
	acceleration = acceleration.GetClampedToMaxSize(maxAcceleration);
	linearVelocity = linearVelocity + acceleration * deltaT;
	linearVelocity = linearVelocity.GetClampedToMaxSize(maxVelocity);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + linearVelocity * deltaT);
}

