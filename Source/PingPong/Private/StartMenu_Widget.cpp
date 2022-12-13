// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_Widget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PingPongGameInstance.h"
#include "BoardPlayerController.h"

void UStartMenu_Widget::NativeOnInitialized() {
	if (StartSessionButton != nullptr) {
		StartSessionButton->OnClicked.AddDynamic(this, &UStartMenu_Widget::Server_StartSession);
	}

	if (JoinSessionButton != nullptr) {
		JoinSessionButton->OnClicked.AddDynamic(this, &UStartMenu_Widget::Server_JoinSession);
	}

	if (ExitGameButton != nullptr) {
		ExitGameButton->OnClicked.AddDynamic(this, &UStartMenu_Widget::ExitGame);
	}
}

void UStartMenu_Widget::Client_StartSession_Implementation() {
	this->RemoveFromViewport();

	// add waiting area to viewport
	ABoardPlayerController* PlayerController = Cast<ABoardPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->ShowWaitingArea();
}

void UStartMenu_Widget::Server_StartSession_Implementation() {
	// start session
	UPingPongGameInstance* PPGameInst = Cast<UPingPongGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PPGameInst->StartGame();

	Client_StartSession();
}

void UStartMenu_Widget::Client_JoinSession_Implementation() {
	this->RemoveFromViewport();

	ABoardPlayerController* PlayerController = Cast<ABoardPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->ShowWaitingArea(FString("Searching for an active game..."));
}


void UStartMenu_Widget::Server_JoinSession_Implementation() {
	// join session

	UPingPongGameInstance* PPGameInst = Cast<UPingPongGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PPGameInst->JoinGame();

	Client_JoinSession();
	// start game
}

void UStartMenu_Widget::ExitGame() {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}