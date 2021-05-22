// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchaeologistGameInstance.h"
#include "ArchaeologistGameModeBase.h"
#include "Archaeologist/GamePlay/Grid.h"
#include "Archaeologist/UMG/GridWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/ArchaeologistSaveGame.h"

void UArchaeologistGameInstance::Save()
{
	if (UArchaeologistSaveGame* SaveGameInstance = Cast<UArchaeologistSaveGame>(UGameplayStatics::CreateSaveGameObject(UArchaeologistSaveGame::StaticClass())))
	{
		AArchaeologistGameModeBase* GameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!GameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("UArchaeologistGameInstance::Save. Invalid GameMode!"));
			return;
		}
		
		// Set data
		SaveGameInstance->AvailableShovel = GameMode->GetAvailableShovel();
		SaveGameInstance->GamePoints = GameMode->GetGamePoints();
		SaveGameInstance->Cells = GameMode->GetGrid()->GetCellsSavingArray();

		// Save data
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotNameString, 0);
	}
}

void UArchaeologistGameInstance::Load()
{	
	if (UArchaeologistSaveGame* LoadedGame = Cast<UArchaeologistSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotNameString, 0)))
	{
		AArchaeologistGameModeBase* GameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!GameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("UArchaeologistGameInstance::Load. Invalid GameMode!"));
			return;
		}
		
		GameMode->AvailableShovel = LoadedGame->AvailableShovel;
		UE_LOG(LogTemp, Warning, TEXT("LOADED: AvailableShovel %i"), LoadedGame->AvailableShovel);
		GameMode->GamePoints = LoadedGame->GamePoints;
		UE_LOG(LogTemp, Warning, TEXT("LOADED: GamePoints %i"), LoadedGame->AvailableShovel);
		GameMode->Grid->SetCells(LoadedGame->Cells);
		UE_LOG(LogTemp, Warning, TEXT("LOADED: Cells count %i"), LoadedGame->Cells.Num());
	}
}