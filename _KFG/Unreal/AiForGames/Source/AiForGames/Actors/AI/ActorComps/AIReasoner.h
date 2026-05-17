// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIActivatable.h"
#include "AIComponent.h"
#include "AIConsideration.h"
#include "Components/ActorComponent.h"
#include "AIReasoner.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UAIReasoner : public UAIComponent
{
	GENERATED_BODY()

	/********************** ATTRIBUTES *********************/
public:

protected:
	TArray<UAIActivatable*>* activatables;
	TArray<UAIActivatable*> activeActivatables;

private:
	
	
	
	/********************** METHODS *********************/
private:

protected:
	void ActivateActivatableWithoutCheck(UAIActivatable* activatable);
	UAIActivatable* ActivateActivatableWithoutCheck(size_t activatableIndex);

public:
	UAIReasoner();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetActivatables(TArray<UAIActivatable*>* activatableList);
	virtual void Process(){}
	virtual UAIActivatable* GetActivatable(UClass* type) const;
	virtual bool ActivateActivatable(UAIActivatable* activatable);
	virtual UAIActivatable* ActivateActivatable(size_t activatableIndex);
	virtual UAIActivatable* ActivateActivatable(UClass* type);
	virtual bool DeactivateActivatable(UAIActivatable* activatable);
	virtual bool DeactivateActivatable(size_t activatableIndex);
};
