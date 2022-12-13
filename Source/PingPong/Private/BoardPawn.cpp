// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPawn.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABoardPawn::ABoardPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(StaticMesh);
	CameraBoom->TargetArmLength = 300.f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ABoardPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoardPawn::Client_MoveRight_Implementation(float Value) {
	FVector Location = this->GetActorLocation();
	FVector RightVector = this->GetActorRightVector();

	this->SetActorLocation(Location + RightVector * Value * MoveRate, true);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("LOL, %s"), *GetActorLocation().ToString()));
}

void ABoardPawn::Multicast_MoveRight_Implementation(float Value) {
	Client_MoveRight(Value);
}

void ABoardPawn::Server_MoveRight_Implementation(float Value) {
	Multicast_MoveRight(Value);
}