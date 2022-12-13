// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	int ScorePlayer1;
	int ScorePlayer2;

public:
	UFUNCTION()
	void IncrementScore(FString PlayerId);

	UFUNCTION()
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
