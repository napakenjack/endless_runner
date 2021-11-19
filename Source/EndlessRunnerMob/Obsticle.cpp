// Fill out your copyright notice in the Description page of Project Settings.


#include "Obsticle.h"
#include "RunningCharacter.h"

// Sets default values
AObsticle::AObsticle()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);

	StaticMesh->OnComponentHit.AddDynamic(this, &AObsticle::OnObsticleHit);
}

void AObsticle::OnObsticleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ARunningCharacter* RunCharacter = Cast<ARunningCharacter>(OtherActor);
	if (RunCharacter)
	{
		RunCharacter->Death();
	}
}



