// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CellWidget.generated.h"

class UCell;

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API UCellWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UGridWidget;

public:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "CellWidget")
	void UpdateWidget();
	
	UFUNCTION(BlueprintPure, Category = "CellWidget")
	FORCEINLINE UCell* GetCell() const { return Cell; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CellWidget")
	UTexture2D* DefaultTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CellWidget")
	UTexture2D* DisabledTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CellWidget")
	UTexture2D* TreasureTexture;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonCell;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ButtonImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextLayer;
	
	UPROPERTY()
	UCell* Cell;

	UFUNCTION()
	void OnCellClicked();
	
	
};
