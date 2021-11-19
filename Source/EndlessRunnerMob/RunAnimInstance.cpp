// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void URunAnimInstance::NativeInitializeAnimation()
{
	if (Runner == nullptr)
	{
		Runner = TryGetPawnOwner();
	}

	if (IsValid(Runner))
	{
		Movement = Runner->GetMovementComponent();
	}
}

void URunAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Runner && Movement)
	{
		bIsInAir = Movement->IsFalling();

		Speed = Runner->GetVelocity().Size();
	}
}
