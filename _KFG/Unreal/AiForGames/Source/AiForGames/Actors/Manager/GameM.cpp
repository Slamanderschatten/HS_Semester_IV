// Copyright © Slamanderschatten. All rights reserved.


#include "GameM.h"


AGameM::AGameM()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AGameM::BeginPlay()
{
	Super::BeginPlay();
	playerController = GetWorld()->GetFirstPlayerController();
	playerController->bShowMouseCursor = true;
	playerController->bEnableMouseOverEvents = true;
	playerController->bEnableClickEvents = true;
}


AActor* AGameM::GetNpcTarget() const
{
	return npcTarget;
}


ENpcTargetInteraction AGameM::GetNpcTargetInteraction() const
{
	return npcTargetInteraction;
}

bool AGameM::IsFlockingEnabled() const
{
	return enableFlocking;
}

TArray<AActor*> AGameM::GetNpcList() const
{
	return npcGround->GetSpawnedActors();
}

void AGameM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetNpcTargetToMousePos();
}


void AGameM::SetNpcTargetToMousePos() const
{
	if (npcTarget == nullptr)
		return;
	FVector WorldLocation;
	FVector WorldDirection;

	if (!playerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		return;

	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_GameTraceChannel1
	);

	if (Hit.bBlockingHit)
	{
		npcTarget->SetActorLocation(Hit.ImpactPoint);
	}
}



