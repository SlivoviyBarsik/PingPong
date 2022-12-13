// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void APingPongGameModeBase::IncrementScore(FString PlayerId) {
	if (PlayerId.Equals(FString("Player 1"))) {
		ScorePlayer1 += 1;
	}
	else if(PlayerId.Equals(FString("Player 2"))) {
		ScorePlayer2 += 1;
	}

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s scored a point"), *PlayerId));
	}
}

void APingPongGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) {
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	if (NewPlayer->GetPawn() == nullptr) {
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
		FTransform ChosenTransform;

		if (PlayerStarts.Num() > 0) {
			FVector Start = PlayerStarts[0]->GetActorLocation() - FVector(100.f, 0.f, 0.f);
			FVector Forward = PlayerStarts[0]->GetActorForwardVector();

			TArray<FHitResult> OutHits;
			TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

			TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

			UKismetSystemLibrary::LineTraceMultiForObjects(
				GetWorld(),
				Start,
				Start + Forward * 200.f,
				TraceObjectTypes,
				false,
				TArray<AActor*>(),
				EDrawDebugTrace::None,
				OutHits,
				true
			);

			for (FHitResult& HitResult : OutHits) {
				if (HitResult.Actor != nullptr) {
					APawn* Pawn = Cast<APawn>(HitResult.Actor);

					if (Pawn != nullptr) {
						ChosenTransform = PlayerStarts[1]->GetActorTransform();
					}
					else {
						ChosenTransform = PlayerStarts[0]->GetActorTransform();
					}
				}
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("No player starts found")));
			return;
		}

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = NewPlayer;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, ChosenTransform.GetLocation(), ChosenTransform.GetRotation().Rotator(), SpawnInfo);
		NewPlayer->Possess(Pawn);
	}
}