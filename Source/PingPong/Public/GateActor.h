// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateActor.generated.h"

UCLASS()
class PINGPONG_API AGateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	FString PlayerId;

	UFUNCTION(BlueprintImplementableEvent)
	void ReactToStrike();

	UFUNCTION(BlueprintCallable)
	void ReactToStrike_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
