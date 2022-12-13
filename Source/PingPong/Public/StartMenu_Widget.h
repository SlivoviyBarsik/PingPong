// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartMenu_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UStartMenu_Widget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_StartSession();

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_StartSession();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_JoinSession();

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_JoinSession();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* StartSessionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* JoinSessionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ExitGameButton;
};
