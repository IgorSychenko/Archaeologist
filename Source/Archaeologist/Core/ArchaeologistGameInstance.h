// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArchaeologistGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API UArchaeologistGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Save();
	
	UFUNCTION()
	void Load();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Saving")
	FString SlotNameString = "DefaultSlot";
	
};
