// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obsticle.generated.h"

UCLASS()
class ENDLESSRUNNERMOB_API AObsticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMesh;

	AObsticle();

	UFUNCTION()
		void OnObsticleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
