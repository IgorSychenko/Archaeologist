// Fill out your copyright notice in the Description page of Project Settings.


#include "CellWidget.h"

#include "Archaeologist/GamePlay/Cell.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool UCellWidget::Initialize()
{
	if (Super::Initialize())
	{
		ButtonCell->OnClicked.AddDynamic(this, &UCellWidget::OnCellClicked);

		UpdateWidget();
		
		return true;
	}

	return false;
}

void UCellWidget::UpdateWidget()
{
	if (!Cell) return;
	TextLayer->SetText(FText::FromString(FString::Printf(TEXT("%i"), Cell->GetCurrentLayer())));
	
	FSlateBrush InBrush = FSlateBrush();

	if (Cell->CanTakeTreasure())
	{
		InBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(TreasureTexture, GetDesiredSize().X, GetDesiredSize().Y);
	}
	else if (Cell->IsOnLastLayer())
	{
		InBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(DisabledTexture, GetDesiredSize().X, GetDesiredSize().Y);		
	}
	else
	{
		InBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(DefaultTexture, GetDesiredSize().X, GetDesiredSize().Y);
	}

	ButtonImage->SetBrush(InBrush);
}

void UCellWidget::OnCellClicked()
{
	if (Cell->IsActive())
	{
		Cell->Dig();

		UpdateWidget();
	}
}