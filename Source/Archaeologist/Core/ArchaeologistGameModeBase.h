// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArchaeologistGameModeBase.generated.h"

class UGridWidget;
class UGrid;
class UPlayerWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverEvent, bool, IsWin);

/**
 * 
 */
UCLASS()
class ARCHAEOLOGIST_API AArchaeologistGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	friend class AArcheologistPlayerController;
	friend class UArchaeologistGameInstance;

public:
	AArchaeologistGameModeBase();

	virtual void BeginPlay() override;

	virtual void Reset() override;

	UFUNCTION(BlueprintCallable, Category = "ArchaeologistGameModeBase")
	void AddGamePoint();
	
	UFUNCTION(BlueprintCallable, Category = "ArchaeologistGameModeBase")
	void DecreaseShovel();
	
	UFUNCTION(BlueprintCallable, Category = "ArchaeologistGameModeBase")
	void CheckEndGame();
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE int32 GetGamePoints() const { return GamePoints; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE int32 GetMaxGamePoints() const { return MaxGamePoints; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE int32 GetAvailableShovel() const { return AvailableShovel; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE int32 GetMaxShovel() const { return MaxShovel; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE UGrid* GetGrid() const { return Grid; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE TSubclassOf<UPlayerWidget> GetDefaultPlayerWidgetClass() const { return DefaultPlayerWidgetClass; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE TSubclassOf<UGridWidget> GetDefaultGridWidgetClass() const { return DefaultGridWidgetClass; };
	
	UFUNCTION(BlueprintPure, Category = "ArchaeologistGameModeBase")
	FORCEINLINE bool IsGameStarted() const { return bIsGameStarted; };
	
	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent OnGameOver;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 GamePoints = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", UIMin = "1"))
	int32 MaxGamePoints = 3;
	
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 AvailableShovel = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game", meta = (ClampMin = "1", UIMin = "1"))
	int32 MaxShovel = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UPlayerWidget> DefaultPlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* DefaultPlayerWidget;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UGridWidget> DefaultGridWidgetClass;

	UPROPERTY()
	UGrid* Grid;

private:
	bool bIsGameStarted = true;
	
};
