// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerMobGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUDWidget.h"



void AEndlessRunnerMobGameModeBase::BeginPlay()
{

	GameHUDWidget = Cast<UGameHUDWidget>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHUDWidget);

	GameHUDWidget->InitializedHUD(this);
	GameHUDWidget->AddToViewport();

	CreateInitialFloor();
}

void AEndlessRunnerMobGameModeBase::CreateInitialFloor()
{
	AFloor* Tile = AddFloor(false);

	if (Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}
		 
	AddFloor(false);
	AddFloor(false);

	for (int i = 0; i < NumInitialFloors; i++)
	{
		AddFloor(true);		
	}
}

AFloor* AEndlessRunnerMobGameModeBase::AddFloor(const bool bSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		AFloor* Tile = World->SpawnActor<AFloor>(FloorClass, NextSpawnPoint);
		if (Tile)
		{
			Floor.Add(Tile);
			if (bSpawnItems)
			{
				Tile->SpawnItems();
			}
			NextSpawnPoint = Tile->GetAttachTrasform();
		}
		return Tile;
	}
	return nullptr;
}



void AEndlessRunnerMobGameModeBase::AddCoin()
{
	TotalCoins += 1;

	OnCoinsCountChanged.Broadcast(TotalCoins);  

}

void AEndlessRunnerMobGameModeBase::PlayerDied()
{
	NumberOfLives -= 1;
	OnLivesCountChanged.Broadcast(NumberOfLives);

	if (NumberOfLives > 0)
	{
		//Iterate all Floor and call DestroyFloor
		for (auto Tile : Floor)
		{
			Tile->DestroyFloor();
		}
		//Empty Array
		Floor.Empty();
		//NextSpawnPoint to initial value
		NextSpawnPoint = FTransform();
		// Create initial floor
		CreateInitialFloor();
		// Broadcast level reset event
		OnLevelReset.Broadcast();
	}
	else
	{
		GameOver();
	}
}

void AEndlessRunnerMobGameModeBase::GameOver()
{
	if (IsValid(GameOverScreenClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), GameOverScreenClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	 }
}

void AEndlessRunnerMobGameModeBase::RemoveFloor(AFloor* Tile)
{
	Floor.Remove(Tile);
}

