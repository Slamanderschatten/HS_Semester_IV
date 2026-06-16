

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIComponent.generated.h"


UCLASS(Abstract, Blueprintable)
class AIFORGAMES_API UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIComponent();

	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
