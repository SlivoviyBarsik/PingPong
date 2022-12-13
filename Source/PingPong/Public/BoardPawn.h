// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GateActor.h"
#include "BoardPawn.generated.h"

UCLASS()
class PINGPONG_API ABoardPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoardPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MoveRate;

	AGateActor* MyGate;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_MoveRight(float Value);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_MoveRight(float Value);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void Multicast_MoveRight(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
