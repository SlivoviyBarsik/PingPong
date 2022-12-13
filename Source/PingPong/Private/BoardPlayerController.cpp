// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPlayerController.h"
#include "BoardPawn.h"
#include "GameFramework/PlayerInput.h"

void ABoardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	this->InputComponent->BindAxis("MoveRight", this, &ABoardPlayerController::MovePawnRight);
}

void ABoardPlayerController::BeginPlay() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("StartMenu")) {
		if (StartMenu_WidgetClass && StartMenu_Widget == nullptr) {
			StartMenu_Widget = CreateWidget<UStartMenu_Widget>(GetWorld(), StartMenu_WidgetClass);
		}

		if (WaitingArea_WidgetClass && WaitingArea_Widget == nullptr) {
			WaitingArea_Widget = CreateWidget<UWaitingArea_Widget>(GetWorld(), WaitingArea_WidgetClass);
		}

		if (Score_WidgetClass && Score_Widget == nullptr) {
			Score_Widget = CreateWidget<UScore_Widget>(GetWorld(), Score_WidgetClass);
		}

		if (StartMenu_Widget != nullptr) {
			StartMenu_Widget->AddToViewport();
			this->SetShowMouseCursor(true);
			this->SetInputMode(FInputModeUIOnly());
		}
	}
	else {
		if (this == GetWorld()->GetFirstPlayerController()) {
			this->PlayerId = FString("Player 1");
		}
		else {
			this->PlayerId = FString("Player 2");
		}

		this->SetShowMouseCursor(false);
		this->SetInputMode(FInputModeGameOnly());

		if (Score_Widget != nullptr) {
			Score_Widget->AddToViewport();
		}
	}
}

void ABoardPlayerController::OnPossess(APawn* NewPawn) {
	ABoardPawn* BPawn = Cast<ABoardPawn>(NewPawn);
	if (BPawn != nullptr) {
		FVector Start = GetPawn()->GetActorLocation();
		FVector Forward = GetPawn()->GetActorForwardVector();

		TArray<FHitResult> OutHits;
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

		TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		UKismetSystemLibrary::BoxTraceMultiForObjects(
			GetWorld(),
			Start,
			Start - Forward * 2000.f,
			FVector(0.5f, 0.5f, 100.f),
			FRotator(),
			TraceObjectTypes,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			OutHits,
			true
		);

		for (FHitResult& HitResult : OutHits) {
			if (HitResult.Actor != nullptr) {
				AGateActor* Gate = Cast<AGateActor>(HitResult.Actor);

				if (Gate != nullptr) {
					Gate->PlayerId = this->PlayerId;
					break;
				}
			}
		}
	}
}

void ABoardPlayerController::MovePawnRight(float Value) {
	if (Value != 0.f) {
		ABoardPawn* ControlledPawn = GetPawn<ABoardPawn>();

		if (ControlledPawn != nullptr) {
			ControlledPawn->Multicast_MoveRight(Value);
		}
	}
}

void ABoardPlayerController::ShowWaitingArea(FString UIText) {
	if(WaitingArea_Widget != nullptr) {
		WaitingArea_Widget->Text->SetText(FText::FromString(UIText));
		WaitingArea_Widget->AddToViewport();

		this->SetShowMouseCursor(true);
		this->SetInputMode(FInputModeUIOnly());
	}
}