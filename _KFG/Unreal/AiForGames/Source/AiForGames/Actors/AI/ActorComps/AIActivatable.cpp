// Copyright © Slamanderschatten. All rights reserved.


#include "AIActivatable.h"


UAIActivatable::UAIActivatable()
{
	bAutoActivate = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UAIActivatable::BeginPlay()
{
	Super::BeginPlay();
	Deactivate();
}


void UAIActivatable::Activate(bool bReset)
{
	Super::Activate(bReset);
	SetComponentTickEnabled(true);
}


void UAIActivatable::Deactivate()
{
	Super::Deactivate();
    SetComponentTickEnabled(false);
}


void UAIActivatable::SetKnowledge(UAIKnowledge* pKnowledge)
{
	knowledge = pKnowledge;
}

