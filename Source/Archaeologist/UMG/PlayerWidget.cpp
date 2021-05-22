// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Archaeologist/Core/ArchaeologistGameModeBase.h"
#include "Kismet/GameplayStatics.h"

bool UPlayerWidget::Initialize()
{
	if (Super::Initialize())
	{
		GameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!GameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("UPlayerWidget::Initialize. Invalid GameMode!"));
		}
		
		RestartButton->OnClicked.AddDynamic(this, &UPlayerWidget::RestartGameClicked);
		
		QuitButton->OnClicked.AddDynamic(this, &UPlayerWidget::QuitClicked);

		UpdateWidget();
		
		return true;		
	}
	
	return false;
}
	
void UPlayerWidget::UpdateWidget()
{	
	if (GameMode)
	{
		const FString GamePointsString = FString::Printf(TEXT("%i/%i"), GameMode->GetGamePoints(), GameMode->GetMaxGamePoints());
		GamePointsText->SetText(FText::FromString(GamePointsString));
	
		const FString ShovelString = FString::Printf(TEXT("%i/%i"), GameMode->GetAvailableShovel(), GameMode->GetMaxShovel());
		ShovelText->SetText(FText::FromString(ShovelString));

		if (GameMode->IsGameStarted())
		{
			GameOverInfo->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			GameOverInfo->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UPlayerWidget::RestartGameClicked()
{
	if (GameMode)
	{
		GameMode->Reset();
	}
}

void UPlayerWidget::QuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}