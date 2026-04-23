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
	UAIConsideration* consideration;

private:
	
	
	
	/********************** METHODS *********************/
private:

protected:

public:
	UAIReasoner();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void SetActivatables(TArray<UAIActivatable*>* activatableList);
	void SetConsideration(UAIConsideration* considerationForThis);
	virtual void Process(){}
};
