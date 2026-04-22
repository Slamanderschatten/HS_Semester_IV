// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIComponent.h"
#include "Components/ActorComponent.h"
#include "AIKnowledge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UAIKnowledge : public UAIComponent
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
	UAIKnowledge();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
