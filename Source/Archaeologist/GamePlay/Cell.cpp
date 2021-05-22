// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Grid.h"
#include "Archaeologist/Core/ArchaeologistGameInstance.h"
#include "Archaeologist/Core/ArchaeologistGameModeBase.h"
#include "Archaeologist/UMG/GridWidget.h"
#include "Kismet/GameplayStatics.h"

void UCell::Initialize(UGrid* NewOwningGrid)
{
	OwningGrid = NewOwningGrid;
	CurrentLayer = MaxDepthLayers;

	// Initialize treasures
	FRandomStream Random;
	Random.GenerateNewSeed();
	
	for (int32 i = 0; i < CurrentLayer; i++)
	{
		if (Random.RandRange(0.0f, 1.0f) <= TreasurePropabilityPerLayer)
		{
			Treasures.Add(true);
		}
		else
		{
			Treasures.Add(false);
		}
	}
}

void UCell::FillBySavingObject(FSavingCell SavingObject)
{
	CurrentLayer = SavingObject.CurrentLayer;
	Treasures = SavingObject.Treasures;
}

void UCell::Dig()
{
	if (IsActive())
	{
		CurrentLayer--;

		if (AArchaeologistGameModeBase* CurrentGameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(OwningGrid->GetGridWidget()->GetWorld())))
		{
			CurrentGameMode->DecreaseShovel();
		}

		if (HasTreasure(CurrentLayer))
		{
			OnTreasureAvailableEvent.Broadcast();
		}

		if (UArchaeologistGameInstance* CurrentGameInstance = Cast<UArchaeologistGameInstance>(OwningGrid->GetGridWidget()->GetGameInstance()))
		{
			CurrentGameInstance->Save();
		}
	}
}

void UCell::TakeTreasure()
{
	if (CanTakeTreasure())
	{
		Treasures[CurrentLayer] = false;

		if (AArchaeologistGameModeBase* CurrentGameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(OwningGrid->GetGridWidget()->GetWorld())))
		{
			CurrentGameMode->AddGamePoint();
		}

		if (UArchaeologistGameInstance* CurrentGameInstance = Cast<UArchaeologistGameInstance>(OwningGrid->GetGridWidget()->GetGameInstance()))
		{
			CurrentGameInstance->Save();
		}

		OnTakeTreasureEvent.Broadcast();
	}
}

FSavingCell UCell::GetSavingObject() const
{
	FSavingCell SavingCellInfo = FSavingCell();

	SavingCellInfo.CurrentLayer = CurrentLayer;
	SavingCellInfo.Treasures = Treasures;

	return SavingCellInfo;
}