// Copyright © Slamanderschatten. All rights reserved.


#include "KinematikFlee.h"

#include "AiForGames/Actors/Npcs/Npc.h"


// Sets default values for this component's properties
UKinematikFlee::UKinematikFlee()
{
}


void UKinematikFlee::SetSeeker(AActor* seeker)
{
	origin = seeker;
}


void UKinematikFlee::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActualizePosition(DeltaTime);
}


void UKinematikFlee::ActualizePosition(float deltaT) const
{
	FVector velocity = GetOwner()->GetActorLocation() - origin->GetActorLocation();
	velocity = velocity.GetClampedToMaxSize(maxVelocity);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + velocity * deltaT);
	npc->Knowledge().SetLinearVelocity(linearVelocity);
}

