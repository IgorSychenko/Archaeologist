// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Archaeologist/Core/Saving/ArchaeologistSaveGame.h"
#include "UObject/NoExportTypes.h"
#include "Grid.generated.h"

class AArchaeologistGameModeBase;
class UArchaeologistGameInstance;
class UCell;
class UGridWidget;

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API UGrid : public UObject
{
	GENERATED_BODY()

	friend UArchaeologistGameInstance;
	friend AArchaeologistGameModeBase;
	friend UGridWidget;

public:
	UFUNCTION(BlueprintPure, Category = "Grid")
	FORCEINLINE TArray<UCell*> GetCells() const { return Cells; }
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	FORCEINLINE UCell* GetCell(int32 Index) const { return Cells.IsValidIndex(Index) ? Cells[Index] : nullptr; }
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	FORCEINLINE UGridWidget* GetGridWidget() const { return GridWidget; }
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool HasAvailableTreasure() const;

	UFUNCTION(BlueprintPure, Category = "Cell")
	TArray<FSavingCell> GetCellsSavingArray() const;
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool IsActive() const;

protected:
	// Base grid size: default 10*10
	UPROPERTY(Category = "Grid", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", UIMin = "1"))
	int32 Size = 10;

	// Set default values and init them
	UFUNCTION()
	void Initialize();

	// Load function
	UFUNCTION()
	void SetCells(TArray<FSavingCell> CellsSavingArray);

private:
	// Cells array in grid
	UPROPERTY()
	TArray<UCell*> Cells;
	
	UPROPERTY()
	UGridWidget* GridWidget;
	
};
