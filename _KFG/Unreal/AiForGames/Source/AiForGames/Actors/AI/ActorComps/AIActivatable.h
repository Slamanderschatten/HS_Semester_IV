// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIComponent.h"
#include "Components/ActorComponent.h"
#include "AIActivatable.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UAIActivatable : public UAIComponent
{
	GENERATED_BODY()

	/********************** ATTRIBUTES *********************/
public:
	UPROPERTY(EditAnywhere, Category="Test")
	int test;

protected:

private:
	/********************** METHODS *********************/
private:

protected:

public:
	UAIActivatable();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
