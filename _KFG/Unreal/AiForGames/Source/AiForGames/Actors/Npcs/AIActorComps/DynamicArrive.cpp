// Copyright © Slamanderschatten. All rights reserved.


#include "DynamicArrive.h"

#include "AiForGames/Actors/Npcs/Npc.h"


// Sets default values for this component's properties
UDynamicArrive::UDynamicArrive()
{

	// ...
}


void UDynamicArrive::SetTarget(AActor* seeker)
{
	origin = seeker;
}


// Called every frame
void UDynamicArrive::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActualizePosition(DeltaTime);
}


void UDynamicArrive::ActualizePosition(float deltaT)
{
	FVector acceleration = origin->GetActorLocation() - GetOwner()->GetActorLocation();
	if (acceleration.Length() < targetRadius)
	{
		linearVelocity = FVector::ZeroVector;
	}
	else
	{
		acceleration = acceleration.GetClampedToMaxSize(maxAcceleration);
		linearVelocity = linearVelocity + acceleration * deltaT;
		linearVelocity *= breakFactor;
		linearVelocity = linearVelocity.GetClampedToMaxSize(maxVelocity);
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + linearVelocity * deltaT);
	}
	npc->Knowledge().SetLinearVelocity(linearVelocity);
}

