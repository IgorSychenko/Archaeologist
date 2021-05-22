// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "GridWidget.generated.h"

class UGrid;

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API UGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	TSubclassOf<UCellWidget> CellWidgetClass = UCellWidget::StaticClass();
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE UGrid* GetGrid() const { return Grid; };
	
	UFUNCTION(BlueprintCallable, Category = "ArchaeologistGameModeBase")
	void UpdateWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* GridPanel;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* BagWidget;

private:
	UPROPERTY()
	UGrid* Grid;
	
};
