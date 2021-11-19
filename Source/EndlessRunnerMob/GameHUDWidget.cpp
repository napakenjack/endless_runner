// Fill out your copyright notice in the Description page of Project Settings.



#include "GameHUDWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameHUDWidget::NativeConstruct()
{
	if (PauseBtn)
	{
		PauseBtn->OnClicked.AddDynamic(this, &UGameHUDWidget::OnPauseClick);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUI(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGameHUDWidget::InitializedHUD(AEndlessRunnerMobGameModeBase* RunGameMode)
{
	if (RunGameMode)
	{
		CoinsCount->SetText(FText::AsNumber(0));
		LivesCount->SetText(FText::AsNumber(RunGameMode->MaxLives));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UGameHUDWidget::SetCoinCount);
		RunGameMode->OnLivesCountChanged.AddDynamic(this, &UGameHUDWidget::SetLivesCount);
	}
}

void UGameHUDWidget::SetCoinCount(const int32 Count)
{
	CoinsCount->SetText(FText::AsNumber(Count));
}

void UGameHUDWidget::SetLivesCount(const int32 Count)
{
	LivesCount->SetText(FText::AsNumber(Count));
}

void UGameHUDWidget::OnPauseClick()
{	
	if (IsValid(PauseMenuWidgetClass))
	{

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}