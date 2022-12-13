// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Score_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UScore_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ThisPlayerId;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ThisPlayerScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* OtherPlayerId;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* OtherPlayerScore;

public:
	FString SThisPlayerId;

	void UpdateScore(FString PlayerId, int NewScore);
};
