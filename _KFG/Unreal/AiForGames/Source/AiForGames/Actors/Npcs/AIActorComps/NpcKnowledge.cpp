// Copyright © Slamanderschatten. All rights reserved.


#include "NpcKnowledge.h"

#include "AiForGames/Actors/Manager/GameM.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UNpcKnowledge::UNpcKnowledge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UNpcKnowledge::BeginPlay()
{
	Super::BeginPlay();
	gameManager = Cast<AGameM>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameM::StaticClass()));
}


ENpcTargetInteraction UNpcKnowledge::GetNpcTargetInteraction() const
{
	return gameManager->GetNpcTargetInteraction();
}

AActor* UNpcKnowledge::GetNpcTarget() const
{
	return gameManager->GetNpcTarget();
}

void UNpcKnowledge::SetLinearVelocity(const FVector& NewLinearVelocity)
{
	linearVelocity = NewLinearVelocity;
}
FVector UNpcKnowledge::GetLinearVelocity() const
{
	return linearVelocity;
}

TArray<AActor*> UNpcKnowledge::GetNpcActors() const
{
	return gameManager->GetNpcList();
}

bool UNpcKnowledge::IsFlockingEnabled() const
{
	return gameManager->IsFlockingEnabled();
}

