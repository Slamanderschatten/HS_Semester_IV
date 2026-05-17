// Copyright © Slamanderschatten. All rights reserved.


#include "GameM.h"


AActor* AGameM::GetNpcTarget() const
{
	return npcTarget;
}


ENpcTargetInteraction AGameM::GetNpcTargetInteraction() const
{
	return npcTargetInteraction;
}

void AGameM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetNpcTargetToMousePos();
}


void AGameM::SetNpcTargetToMousePos()
{
	if (npcTarget == nullptr)
		return;
	FVector WorldLocation;
	FVector WorldDirection;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility
	);
	if (Hit.bBlockingHit)
	{
		npcTarget->SetActorLocation(Hit.Location);
	}
}

