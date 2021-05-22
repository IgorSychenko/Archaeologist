// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Grid.h"
#include "Archaeologist/Core/Saving/ArchaeologistSaveGame.h"
#include "UObject/NoExportTypes.h"
#include "Cell.generated.h"

class AArchaeologistGameModeBase;
class UGrid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeTreasureEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTreasureAvailableEvent);

/**
 * 
 */

UCLASS()
class ARCHAEOLOGIST_API UCell : public UObject
{
	GENERATED_BODY()

	friend UGrid;

public:
	UFUNCTION(BlueprintPure, Category = "Cell")
	FORCEINLINE int32 GetCurrentLayer() const { return CurrentLayer; }
	
	UFUNCTION(BlueprintPure, Category = "Cell")
	FORCEINLINE bool IsOnLastLayer() const { return CurrentLayer == 0; }
	
	UFUNCTION(BlueprintPure, Category = "Cell")
	FORCEINLINE bool HasTreasure(int32 Layer) const { return Treasures.IsValidIndex(Layer) ? Treasures[Layer] : false; }
	
	UFUNCTION(BlueprintPure, Category = "Cell")
	FORCEINLINE bool CanTakeTreasure() const { return HasTreasure(CurrentLayer); }

	UFUNCTION(BlueprintPure, Category = "Cell")
	FORCEINLINE bool IsActive() const { return !IsOnLastLayer() && !CanTakeTreasure() && OwningGrid->IsActive(); }

	UFUNCTION(BlueprintPure, Category = "Cell")
	FSavingCell GetSavingObject() const;

	// Dig to next layer
	UFUNCTION(BlueprintCallable, Category = "Cell")
	void Dig();

	UFUNCTION(BlueprintCallable, Category = "Cell")
	void TakeTreasure();
	
	UPROPERTY(BlueprintAssignable, Category = "ArchaeologistBlock")
	FTakeTreasureEvent OnTakeTreasureEvent;

	UPROPERTY(BlueprintAssignable, Category = "ArchaeologistBlock")
	FTreasureAvailableEvent OnTreasureAvailableEvent;

protected:
	UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 MaxDepthLayers = 3;

	UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	float TreasurePropabilityPerLayer = 0.2;

	// Set default values and init then
	UFUNCTION()
	void Initialize(UGrid* NewOwningGrid);

	UFUNCTION(BlueprintCallable, Category = "Cell")
	void FillBySavingObject(FSavingCell SavingObject);

private:
	UPROPERTY()
	UGrid* OwningGrid;

	UPROPERTY()
	int32 CurrentLayer;

	// Has layer treasure or not
	UPROPERTY()
	TArray<bool> Treasures;
	
};
