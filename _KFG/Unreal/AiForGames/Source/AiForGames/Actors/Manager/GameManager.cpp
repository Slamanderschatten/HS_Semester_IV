// Copyright © Slamanderschatten. All rights reserved.


#include "GameManager.h"


AGameManager::AGameManager()
{
	if (instance != nullptr)
	{
		this->Destroy();
		return;
	}
	instance = this;
}


AActor* AGameManager::GetNpcTarget() const
{
	return npcTarget;
}


UNpcTargetInteraction AGameManager::GetNpcTargetInteraction() const
{
	return npcTargetInteraction;
}
