// Copyright © Slamanderschatten. All rights reserved.


#include "KinematicSeek.h"


// Sets default values for this component's properties
UKinematicSeek::UKinematicSeek()
{
}


void UKinematicSeek::SetTarget(AActor* target)
{
	origin = target;
}


void UKinematicSeek::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActualizePosition(DeltaTime);
}


void UKinematicSeek::ActualizePosition(float deltaT) const
{
	FVector velocity = origin->GetActorLocation() - GetOwner()->GetActorLocation();
	velocity = velocity.GetClampedToMaxSize(maxVelocity);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + velocity * deltaT);
}

