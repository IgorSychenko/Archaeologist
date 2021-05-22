// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerWidget.generated.h"

class AArchaeologistGameModeBase;

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
	void UpdateWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GamePointsText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShovelText;

	UPROPERTY(meta = (BindWidget))
	UBorder* GameOverInfo; 

	UFUNCTION()
	void RestartGameClicked();

	UFUNCTION()
	void QuitClicked();

private:
	UPROPERTY()
	AArchaeologistGameModeBase* GameMode;
	
};
