// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "CoinItem.h"
#include "Obsticle.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "RunningCharacter.h"
#include "EndlessRunnerMobGameModeBase.h"




// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	CenterLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	RightLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	LeftLane->SetupAttachment(SceneComponent);

	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn")); 

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	RunGameMode = Cast<AEndlessRunnerMobGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(RunGameMode);

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, & AFloor::OnTriggerBoxOverlap);
}

void AFloor::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunningCharacter* RunningCharacter = Cast<ARunningCharacter>(OtherActor);

	if (RunningCharacter)
	{
		RunGameMode->AddFloor(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloor::DestroyFloor, 2.f, false);

	}
}

void AFloor::SpawnItems()
{
	if (IsValid(SmallObsticleClass) && IsValid(BigObsticleClass) && IsValid(CoinItemClass))
	{
		int32 NumBigs = 0;
		SpawnLaneItem(CenterLane, NumBigs);
		SpawnLaneItem(LeftLane, NumBigs);
		SpawnLaneItem(RightLane, NumBigs);
	}

}

void AFloor::SpawnLaneItem(UArrowComponent* Lane, int32& NumBigs)
{
	const float RandVal = FMath::FRandRange(0.f, 1.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent1, SpawnPercent2, true, true))
	{
		AObsticle* Obsticle = GetWorld()->SpawnActor<AObsticle>(SmallObsticleClass, SpawnLocation, SpawnParameters);
		ChildActors.Add(Obsticle);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent2, SpawnPercent3, true, true))
	{
		if (NumBigs <= 2)
		{
		
			AObsticle* Obsticle = GetWorld()->SpawnActor<AObsticle>(BigObsticleClass, SpawnLocation, SpawnParameters);
			
			if (Obsticle)
			{
				NumBigs += 1;
			}
			ChildActors.Add(Obsticle);
		}
		else
		{
			AObsticle* Obsticle = GetWorld()->SpawnActor<AObsticle>(SmallObsticleClass, SpawnLocation, SpawnParameters);
			ChildActors.Add(Obsticle);
		}
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent3, 1.f, true, true))
	{
		ACoinItem* Coin = GetWorld()->SpawnActor<ACoinItem>(CoinItemClass, SpawnLocation, SpawnParameters);
		ChildActors.Add(Coin);
	}
}

void AFloor::DestroyFloor()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	for (auto Child : ChildActors)
	{
		if (IsValid(Child))
		{
			Child->Destroy();
		}
	}

	ChildActors.Empty();

	RunGameMode->RemoveFloor(this);

	this->Destroy();
}

