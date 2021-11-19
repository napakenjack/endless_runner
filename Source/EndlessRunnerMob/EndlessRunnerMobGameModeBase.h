// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Floor.h"
#include "Blueprint/UserWidget.h"
#include "EndlessRunnerMobGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, LivesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERMOB_API AEndlessRunnerMobGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget>GameHudClass;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<AFloor>FloorClass;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameOverScreenClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UGameHUDWidget* GameHUDWidget;

	UPROPERTY(VisibleAnywhere)
		int32 TotalCoins = 0;

	UPROPERTY(VisibleAnywhere)
		int32 NumberOfLives = 0;

	UPROPERTY(VisibleAnywhere)
		int32 MaxLives = 3;

	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumInitialFloors = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		FTransform NextSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		TArray<float> LaneSwitchValues;

	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		TArray<AFloor*> Floor;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnLivesCountChanged OnLivesCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnLevelReset OnLevelReset;

	UFUNCTION(BlueprintCallable)
		void CreateInitialFloor();

	UFUNCTION(BlueprintCallable)
		AFloor* AddFloor(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable)
		void AddCoin();

	UFUNCTION(BlueprintCallable)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		void PlayerDied();

	UFUNCTION(BlueprintCallable)
		void RemoveFloor(AFloor* Tile);


protected:

	virtual void BeginPlay() override;
};
