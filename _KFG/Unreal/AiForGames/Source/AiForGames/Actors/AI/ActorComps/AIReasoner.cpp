// Copyright © Slamanderschatten. All rights reserved.


#include "AIReasoner.h"

#include "AiForGames/Actors/Manager/GameManager.h"


// Sets default values for this component's properties
UAIReasoner::UAIReasoner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIReasoner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIReasoner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Process();
}


void UAIReasoner::SetActivatables(TArray<UAIActivatable*>* activatableList)
{
	activatables = activatableList;
}


void UAIReasoner::SetConsideration(UAIConsideration* considerationForThis)
{
	this->consideration = considerationForThis;
}

