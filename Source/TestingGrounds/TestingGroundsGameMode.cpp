// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestingGroundsGameMode.h"
#include "TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

ATestingGroundsGameMode::ATestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behavior/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundsHUD::StaticClass();

	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void ATestingGroundsGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void ATestingGroundsGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);

}
