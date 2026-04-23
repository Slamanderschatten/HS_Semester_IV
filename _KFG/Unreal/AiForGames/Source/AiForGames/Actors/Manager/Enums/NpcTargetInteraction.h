// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "NpcTargetInteraction.generated.h"

/**
 * option what the npc instances do with the target
 */
UENUM(BlueprintType)
enum class UNpcTargetInteraction : uint8
{
	FleeKinematic,
	FleeDynamic,
	SeekKinematic,
	SeekDynamic,
	
	
	
};
