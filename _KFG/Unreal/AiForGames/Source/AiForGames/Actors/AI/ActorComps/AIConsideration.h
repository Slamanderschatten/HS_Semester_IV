// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIComponent.h"
#include "Components/ActorComponent.h"
#include "AIConsideration.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UAIConsideration : public UAIComponent
{
	GENERATED_BODY()

	/********************** ATTRIBUTES *********************/
public:

protected:

private:
	/********************** METHODS *********************/
private:

protected:

public:
	UAIConsideration();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
