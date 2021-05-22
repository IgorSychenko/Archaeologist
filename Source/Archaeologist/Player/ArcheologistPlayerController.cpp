// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcheologistPlayerController.h"
#include "Archaeologist/Core/ArchaeologistGameModeBase.h"
#include "Archaeologist/UMG/GridWidget.h"
#include "Archaeologist/UMG/PlayerWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

AArcheologistPlayerController::AArcheologistPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AArcheologistPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	// Initialize widgets
	InitViewport();
}

void AArcheologistPlayerController::InitViewport()
{
	AArchaeologistGameModeBase* ArchaeologistGameMode = Cast<AArchaeologistGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (ArchaeologistGameMode)
    {
    	// Init player widget
    	if (PlayerWidget)
    	{
    		PlayerWidget->RemoveFromParent();
    	}
    	
    	PlayerWidget = CreateWidget<UPlayerWidget>(this, ArchaeologistGameMode->GetDefaultPlayerWidgetClass().Get());
    	PlayerWidget->AddToViewport(1);

    	ArchaeologistGameMode->DefaultPlayerWidget = PlayerWidget;

    	// Init grid widget   
    	if (GridWidget)
    	{
    		GridWidget->RemoveFromParent();
    	}	
    	GridWidget = CreateWidget<UGridWidget>(this, ArchaeologistGameMode->GetDefaultGridWidgetClass().Get());
    	GridWidget->AddToViewport(0);
    }
    else
    {
    	UE_LOG(LogTemp, Error, TEXT("AArcheologistPlayerController::BeginPlay. Invalid GameMode!"));
    }
}