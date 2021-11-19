// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obsticle.h"
#include "CoinItem.h"
#include "Floor.generated.h"


UCLASS()
class ENDLESSRUNNERMOB_API AFloor : public AActor
{
	GENERATED_BODY()
	

public:		

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObsticle> SmallObsticleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObsticle> BigObsticleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<ACoinItem> CoinItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* FloorTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AActor*> ChildActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent1 = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent2 = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent3 = 0.5f;

	UFUNCTION(BlueprintCallable)
		void SpawnItems();

	UFUNCTION(BlueprintCallable)
		void DestroyFloor();


	// Sets default values for this actor's properties
	AFloor();

	FORCEINLINE const FTransform& GetAttachTrasform() const
	{
		return AttachPoint->GetComponentTransform();
	}

protected:

	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerMobGameModeBase* RunGameMode;

	UPROPERTY()
		FTimerHandle DestroyHandle;

	UFUNCTION()
		void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void SpawnLaneItem(UArrowComponent* Lane, int32& NumBigs);

	

	virtual void BeginPlay() override;
};
