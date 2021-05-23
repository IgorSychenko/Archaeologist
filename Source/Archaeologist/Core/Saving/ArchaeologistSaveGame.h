// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ArchaeologistSaveGame.generated.h"

/**
 * 
 */

// Cell saving struct for savefile size reduction 
USTRUCT(BlueprintType)
struct FSavingCell
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 CurrentLayer;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<bool> Treasures;
};

UCLASS()
class ARCHAEOLOGIST_API UArchaeologistSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UArchaeologistSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 GamePoints;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 AvailableShovel;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<FSavingCell> Cells;
		
};
