// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "StartMenu_Widget.h"
#include "WaitingArea_Widget.h"
#include "Score_Widget.h"
#include "BoardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API ABoardPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MovePawnRight(float Value);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UStartMenu_Widget> StartMenu_WidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWaitingArea_Widget> WaitingArea_WidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UScore_Widget> Score_WidgetClass;

	UPROPERTY(EditAnywhere)
	class UStartMenu_Widget* StartMenu_Widget;

	UPROPERTY(EditAnywhere)
	class UWaitingArea_Widget* WaitingArea_Widget;

	UPROPERTY(EditAnywhere)
	class UScore_Widget* Score_Widget;

public:
	void ShowWaitingArea(FString UIText = FString("Waiting for another player to join..."));

	virtual void OnPossess(APawn* Pawn) override;

	FString PlayerId;
};
