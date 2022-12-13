// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GateActor.h"
#include "PingPong/PingPongGameModeBase.h"

// Sets default values
ABallActor::ABallActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	this->InitTransform();
	
	if (CollisionSphere != nullptr) {
		CollisionSphere->OnComponentHit.AddUniqueDynamic(this, &ABallActor::OnHit);
	}
}

void ABallActor::InitTransform() {
	InitLocation = FVector(FMath::RandRange(150.f, 850.f), 790.f, 120.f);
	InitRotation = FRotator(0.f, FMath::RandRange(0.f, 180.f), 0.f);

	SetActorLocation(InitLocation);
	SetActorRotation(InitRotation);
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Direction = GetActorForwardVector();

	//UKismetSystemLibrary::DrawDebugArrow(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector(), 5.f, FColor::Red, 5.f, 0.5f);

	FHitResult OutHit;
	bool res = SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true, &OutHit);
}

void ABallActor::OnHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit
) {
	AGateActor* Gate = Cast<AGateActor>(OtherActor);

	if (Gate != nullptr) {
		// inform server
		Gate->ReactToStrike();

		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		if(BP_Ball != nullptr)
			GetWorld()->SpawnActor<ABallActor>(BP_Ball, FVector(500.f, 790.f, 120.f), FRotator());

		this->Destroy();
	}
	else {
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Colliding!"));*/

		FVector ForwardVec = GetActorForwardVector();

		FVector ProjNorm = UKismetMathLibrary::ProjectVectorOnToVector(ForwardVec, Hit.ImpactNormal);
		FVector DesiredForwardVec = ForwardVec - 2 * ProjNorm;

		SetActorRotation(DesiredForwardVec.Rotation());
	}
}

