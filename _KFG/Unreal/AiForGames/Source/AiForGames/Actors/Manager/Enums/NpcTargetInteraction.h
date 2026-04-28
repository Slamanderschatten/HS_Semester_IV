// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NpcTargetInteraction.generated.h"

/**
 * option what the npc instances do with the target
 */
UENUM(BlueprintType)
enum class ENpcTargetInteraction : uint8
{
	FleeKinematic,
	FleeDynamic,
	SeekKinematic,
	SeekDynamic,
	
	
	
};
