// Copyright © Slamanderschatten. All rights reserved.


#include "GameManager.h"


AGameManager::AGameManager()
{
	instance = this;
}


AActor* AGameManager::GetNpcTarget() const
{
	return npcTarget;
}


ENpcTargetInteraction AGameManager::GetNpcTargetInteraction() const
{
	return npcTargetInteraction;
}


AGameManager* AGameManager::instance = nullptr;
