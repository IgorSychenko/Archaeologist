// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArcheologistPlayerController.generated.h"

class UGridWidget;
class UPlayerWidget;

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API AArcheologistPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArcheologistPlayerController();

	virtual void BeginPlay() override;

	// Initialize widgets
	void InitViewport();

private:
	UPROPERTY()
	UPlayerWidget* PlayerWidget;
	
	UPROPERTY()
	UGridWidget* GridWidget;
	
};
