// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunningCharacter.generated.h"

UCLASS()
class ENDLESSRUNNERMOB_API ARunningCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraComponent", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraComponent", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerMobGameModeBase* RunGameMode;


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MoveDownImpulse = -1000.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 NextLane = 0;

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
		void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneUpdate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable)
		void Death();

	// Sets default values for this character's properties
	ARunningCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnDeath();

	UFUNCTION()
	void MoveRight();

	UFUNCTION()
	void MoveLeft();

	UFUNCTION()
	void MoveDown();

	UFUNCTION()
		void ResetLevel();

	UPROPERTY()
		class APlayerStart* PlayerStart;

	UPROPERTY()
		FTimerHandle RestartTimerHandle;

	UPROPERTY()
		bool bIsDead = false;

public:	

	UFUNCTION()
		void AddCoin();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
