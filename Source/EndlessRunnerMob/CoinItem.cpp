// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "RunningCharacter.h"

// Sets default values
ACoinItem::ACoinItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(SphereCollider);
	CoinMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);

}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, & ACoinItem::OnSphereOverlap);
}

void ACoinItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ARunningCharacter* RunningCharacter = Cast<ARunningCharacter>(OtherActor);

	if (RunningCharacter)
	{
		if(OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		}
		RunningCharacter->AddCoin();

		Destroy();
	}
}



