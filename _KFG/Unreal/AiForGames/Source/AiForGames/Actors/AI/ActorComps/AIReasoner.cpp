// Copyright © Slamanderschatten. All rights reserved.


#include "AIReasoner.h"

#include <rapidjson/rapidjson.h>

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


UAIActivatable* UAIReasoner::GetActivatable(UClass* type) const
{
	for (UAIActivatable* activatable : *activatables)
	{
		if (activatable->IsA(type))
			return activatable;
	}
	return nullptr;
}


void UAIReasoner::ActivateActivatableWithoutCheck(UAIActivatable* activatable)
{
	activeActivatables.Push(activatable);
	activatable->Activate();
}


UAIActivatable* UAIReasoner::ActivateActivatableWithoutCheck(size_t activatableIndex)
{
	ActivateActivatableWithoutCheck((*activatables)[activatableIndex]);
	return (*activatables)[activatableIndex];
}


UAIActivatable* UAIReasoner::ActivateActivatable(size_t activatableIndex)
{
	if (activatableIndex <= activatables->Num() || (*activatables)[activatableIndex]->IsActive())
		return nullptr;
	return ActivateActivatableWithoutCheck(activatableIndex);
}


bool UAIReasoner::ActivateActivatable(UAIActivatable* activatable)
{
	size_t activatableIndex = activatables->Find(activatable);
	if (activatableIndex == INDEX_NONE || activatable->IsActive())
		return false;
	ActivateActivatableWithoutCheck(activatableIndex);
	return true;
}


UAIActivatable* UAIReasoner::ActivateActivatable(UClass* type)
{
	UAIActivatable* activatable = GetActivatable(type);
	if (activatable)
		ActivateActivatableWithoutCheck(activatable);
	return activatable;
}


bool UAIReasoner::DeactivateActivatable(size_t activatableIndex)
{
	if (activatableIndex >= activeActivatables.Num())
		return false;
	activeActivatables[activatableIndex]->Deactivate();
	activeActivatables.RemoveAt(activatableIndex);
	return true;
}


bool UAIReasoner::DeactivateActivatable(UAIActivatable* activatable)
{
	size_t activatableIndex = activatables->Find(activatable);
	if (activatableIndex == INDEX_NONE)
		return false;
	return DeactivateActivatable(activatableIndex);
}

