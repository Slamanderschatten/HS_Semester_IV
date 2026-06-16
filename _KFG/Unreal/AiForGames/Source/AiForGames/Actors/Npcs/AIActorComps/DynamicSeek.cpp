// Copyright © Slamanderschatten. All rights reserved.


#include "DynamicSeek.h"

#include "AiForGames/Actors/Npcs/Npc.h"


// Sets default values for this component's properties
UDynamicSeek::UDynamicSeek()
{
}
void UDynamicSeek::SetTarget(AActor* target)
{
	origin = target;
}


// Called every frame
void UDynamicSeek::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AutoGetTarget();
	ActualizePosition(DeltaTime);
}


void UDynamicSeek::AutoGetTarget()
{
	SetTarget(npc->Knowledge().GetGameManager().GetNpcTarget());
}


void UDynamicSeek::ActualizePosition(float deltaT)
{
	FVector acceleration = origin->GetActorLocation() - GetOwner()->GetActorLocation();
	acceleration = acceleration.GetClampedToMaxSize(maxAcceleration);
	linearVelocity = linearVelocity + acceleration * deltaT;
	linearVelocity = linearVelocity.GetClampedToMaxSize(maxVelocity);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + linearVelocity * deltaT);
	npc->Knowledge().SetLinearVelocity(linearVelocity);
}

