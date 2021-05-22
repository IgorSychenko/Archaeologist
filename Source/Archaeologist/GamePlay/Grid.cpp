// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Cell.h"
#include "Archaeologist/Core/ArchaeologistGameModeBase.h"
#include "Archaeologist/UMG/GridWidget.h"
#include "Kismet/GameplayStatics.h"

void UGrid::Initialize()
{
	Cells.Empty();
	
	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		UCell* Cell = NewObject<UCell>();

		if (Cell)
		{
			Cell->Initialize(this);
			Cells.Add(Cell);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UGrid::Initialize. Cell is not spawned!"));
		}
	}
}

void UGrid::SetCells(TArray<FSavingCell> CellsSavingArray)
{
	Cells.Empty();

	for (auto LoadedCell : CellsSavingArray)
	{
		UCell* NewCell = NewObject<UCell>();
		NewCell->FillBySavingObject(LoadedCell);
		NewCell->OwningGrid = this;
		Cells.Add(NewCell);
	}

	if (GridWidget)
	{
		GridWidget->UpdateWidget();
	}
}

bool UGrid::HasAvailableTreasure() const
{
	for (UCell* Cell : Cells)
	{
		if (Cell->CanTakeTreasure()) return true;
	}

	return false;
}

bool UGrid::IsActive() const
{
	if (AArchaeologistGameModeBase* ArchaeologistGameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetGridWidget()->GetWorld())))
	{
		return ArchaeologistGameMode->IsGameStarted();
	}

	return false;
}

TArray<FSavingCell> UGrid::GetCellsSavingArray() const
{
	TArray<FSavingCell> CellsSavingObject;

	for (auto cell : Cells)
	{
		CellsSavingObject.Add(cell->GetSavingObject());
	}

	return CellsSavingObject;
}