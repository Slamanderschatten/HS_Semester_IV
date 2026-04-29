// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIComponent.h"
#include "AIKnowledge.h"
#include "Components/ActorComponent.h"
#include "AIActivatable.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AIFORGAMES_API UAIActivatable : public UAIComponent
{
	GENERATED_BODY()

	/********************** ATTRIBUTES *********************/
public:

protected:
	UAIKnowledge* knowledge;

private:
	
	
	
	
	
	
	/********************** METHODS *********************/

public:
	UAIActivatable();
	virtual void BeginPlay() override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	void SetKnowledge(UAIKnowledge* knowledge);

protected:
	
private:
	
	
	
};
