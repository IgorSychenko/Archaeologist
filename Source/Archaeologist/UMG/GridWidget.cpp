// Fill out your copyright notice in the Description page of Project Settings.


#include "GridWidget.h"
#include "Archaeologist/Core/ArchaeologistGameModeBase.h"
#include "Archaeologist/GamePlay/Grid.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/GameplayStatics.h"

bool UGridWidget::Initialize()
{
	if (Super::Initialize())
	{
		// Initialize grid
		AArchaeologistGameModeBase* ArchaeologistGameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if (!ArchaeologistGameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("UGridWidget::Initialize. Invalid GameMode!"));
			return false;
		}
		Grid = ArchaeologistGameMode->GetGrid();
		
		if (Grid)
		{
			Grid->GridWidget = this;

			// Spawn grid cells
			int32 RowIndex = 0;
			int32 ColumnIndex = 0;
			for (UCell* Cell : Grid->GetCells())
			{
				if (UCellWidget* CellWidget = CreateWidget<UCellWidget>(this, CellWidgetClass))
				{
					CellWidget->Cell = Cell;
					CellWidget->UpdateWidget();

					if (GridPanel)
					{
						UUniformGridSlot* NewSlot = GridPanel->AddChildToUniformGrid(CellWidget, RowIndex, ColumnIndex);
						NewSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
						NewSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("UGridWidget::Initialize. GridPanel is null!"));
					}

					ColumnIndex++;
					if (ColumnIndex >= Grid->Size)
					{
						ColumnIndex = 0;
						RowIndex++;
					}
				}
			}

			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UGridWidget::Initialize. Grid is null!"));
		}
	}

	return false;
}

void UGridWidget::UpdateWidget()
{
	int32 counter = 0;
	for (auto Child : GridPanel->GetAllChildren())
	{
		if (UCellWidget* CellWidget = Cast<UCellWidget>(Child))
		{
			if (UCell* Cell = Grid->GetCell(counter))
			{
				CellWidget->Cell = Cell;
			}
			
			CellWidget->UpdateWidget();
			counter++;
		}
	}
}