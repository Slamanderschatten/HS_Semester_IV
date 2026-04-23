// Copyright © Slamanderschatten. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enums/NpcTargetInteraction.h"
#include "GameManager.generated.h"

UCLASS()
class AIFORGAMES_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Npcs")
	AActor* npcTarget;
	UPROPERTY(EditAnywhere, Category="Npcs")
	UNpcTargetInteraction npcTargetInteraction = UNpcTargetInteraction::SeekKinematic;

	
	
protected:
	
private:
	static AGameManager* instance;
	
	
	
	
	
public:
	AGameManager();
	static AGameManager* I() {return instance;}
	AActor* GetNpcTarget() const;
	UNpcTargetInteraction GetNpcTargetInteraction() const;

	
protected:
	
private:
	
	
	
	
	
	
};
