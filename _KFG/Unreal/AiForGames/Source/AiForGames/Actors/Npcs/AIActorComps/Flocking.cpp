// Copyright © Slamanderschatten. All rights reserved.


#include "Flocking.h"

#include "AiForGames/Actors/Npcs/Npc.h"


// Sets default values for this component's properties
UFlocking::UFlocking()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


FVector UFlocking::FlockingForce(FVector targetDirection) const
{
	FVector velocity = npc->Knowledge().GetLinearVelocity();
	FVector velocitySum = FVector::ZeroVector;
	int influenceCount = 0;
	FVector separationForce = FVector::ZeroVector;
	int separationCount = 0;
	FVector cohesionForce = FVector::ZeroVector;
	int cohesionCount = 0;
	
	for (AActor* otherNpc : npc->Knowledge().GetNpcActors())
	{
		if (otherNpc == npc)
			continue;
		
		FVector otherDirection = otherNpc->GetActorLocation() - npc->GetActorLocation();
		float distance = FMath::Abs(otherDirection.Length());
		otherDirection.Normalize();
		
		//velocity matching
		if (distance < radiusOfInfluence)
		{
			velocitySum += Cast<ANpc>(otherNpc)->Knowledge().GetLinearVelocity();
			influenceCount++;
			
			//cohesion
			if (distance > radiusOfCohesion)
			{
				cohesionForce += distance * otherDirection;
				cohesionCount++;
			}
		
			//separation
			if (distance < radiusOfSeparation)
			{
				separationForce -= (radiusOfSeparation - distance) * otherDirection;
				separationCount++;
			}
		}
	}
	
	//velocity matching
	FVector velocityForce = FVector::ZeroVector;
	if (influenceCount > 0)
	{
		velocitySum /= influenceCount;
		velocityForce = velocitySum - velocity;
	}
	
	//cohesion
	if (cohesionCount > 0)
	{
		cohesionForce = cohesionForce / cohesionCount / radiusOfInfluence * cohesionMaxForce;
		if (targetDirection.Length() > 0.001f)
		{
			targetDirection.Normalize();
			cohesionForce = FVector::DotProduct(cohesionForce, targetDirection) * targetDirection;
		}
	}
	
	//separation
	if (separationCount > 0)
	{
		separationForce = separationForce * separationMaxForce;
		separationForce /= radiusOfSeparation;
	}
	
	//combine
	FVector force = separationForce + velocityForce + cohesionForce;
	
	return force;
}


void UFlocking::ActualizePosition(float deltaT)
{
	FVector acceleration = origin->GetActorLocation() - GetOwner()->GetActorLocation();
	acceleration += FlockingForce(origin->GetActorLocation());
	acceleration = acceleration.GetClampedToMaxSize(maxAcceleration);
	linearVelocity = linearVelocity + acceleration * deltaT;
	linearVelocity = linearVelocity.GetClampedToMaxSize(maxVelocity);
	FVector pos = npc->GetActorLocation() + linearVelocity * deltaT;
	pos.Set(pos.X, pos.Y, npc->GetActorLocation().Z);
	npc->SetActorLocation(pos);
	npc->Knowledge().SetLinearVelocity(linearVelocity);
}

