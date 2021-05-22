// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArchaeologistGameModeBase.h"
#include "ArchaeologistGameInstance.h"
#include "Archaeologist/GamePlay/Grid.h"
#include "Archaeologist/Player/ArcheologistPlayerController.h"
#include "Archaeologist/UMG/GridWidget.h"
#include "Archaeologist/UMG/PlayerWidget.h"

AArchaeologistGameModeBase::AArchaeologistGameModeBase()
{
	AvailableShovel = MaxShovel;
}

void AArchaeologistGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize grid
	Grid = NewObject<UGrid>();
	Grid->Initialize();

	// Load Game
	if (Cast<UArchaeologistGameInstance>(GetGameInstance()))
	{
		Cast<UArchaeologistGameInstance>(GetGameInstance())->Load();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArchaeologistGameModeBase::BeginPlay. Invalid GameInstance!"));
	}
	
	bIsGameStarted = true;
	CheckEndGame();
}

void AArchaeologistGameModeBase::Reset()
{
	Super::Reset();

	// Reset default values
	AvailableShovel = MaxShovel;
	GamePoints = 0;

	// Initialize grid
	Grid->Initialize();

	bIsGameStarted = true;

	// Update widgets and grid
	AArcheologistPlayerController* Player = Cast<AArcheologistPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Player)
	{
		Player->InitViewport();
	}

	if (Cast<UArchaeologistGameInstance>(GetGameInstance()))
	{
		Cast<UArchaeologistGameInstance>(GetGameInstance())->Save();
	}
	
	Grid->GetGridWidget()->UpdateWidget();
	
}

void AArchaeologistGameModeBase::AddGamePoint()
{
	GamePoints++;

	if (DefaultPlayerWidget)
	{
		DefaultPlayerWidget->UpdateWidget();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArchaeologistGameModeBase::AddGamePoint. DefaultPlayerWidget is null!"));
	}
	
	if (Cast<UArchaeologistGameInstance>(GetGameInstance()))
	{
		Cast<UArchaeologistGameInstance>(GetGameInstance())->Save();
	}
	
	CheckEndGame();
}

void AArchaeologistGameModeBase::DecreaseShovel()
{
	AvailableShovel--;

	if (DefaultPlayerWidget)
	{
		DefaultPlayerWidget->UpdateWidget();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArchaeologistGameModeBase::DecreaseShovel. DefaultPlayerWidget is null!"));
	}

	if (Cast<UArchaeologistGameInstance>(GetGameInstance()))
	{
		Cast<UArchaeologistGameInstance>(GetGameInstance())->Save();
	}

	CheckEndGame();
}

void AArchaeologistGameModeBase::CheckEndGame()
{
	if (GamePoints >= MaxGamePoints)
	{
		OnGameOver.Broadcast(true);
		bIsGameStarted = false;
	}
	else if (AvailableShovel <= 0 && !Grid->HasAvailableTreasure())
	{
		OnGameOver.Broadcast(false);
		bIsGameStarted = false;
	}

	if (DefaultPlayerWidget)
	{
		DefaultPlayerWidget->UpdateWidget();
	}
}
