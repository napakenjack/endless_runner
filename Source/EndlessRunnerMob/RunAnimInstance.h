// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RunAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERMOB_API URunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Movement")
	class APawn* Runner;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Movement")
	class UPawnMovementComponent* Movement;


	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	


};
