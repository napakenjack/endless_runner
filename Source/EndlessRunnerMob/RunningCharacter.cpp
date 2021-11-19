// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EndlessRunnerMobGameModeBase.h"



// Sets default values
ARunningCharacter::ARunningCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->TargetArmLength = 350.f;
	CameraArm->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ARunningCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	RunGameMode = Cast<AEndlessRunnerMobGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);

	RunGameMode->OnLevelReset.AddDynamic(this, &ARunningCharacter::ResetLevel);

	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(),APlayerStart::StaticClass()));
}





void ARunningCharacter::AddCoin()
{
	RunGameMode->AddCoin();
}

// Called every frame
void ARunningCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.f;
	ControlRot.Pitch = 0.f;
	 


	AddMovementInput(ControlRot.Vector());
}


// Called to bind functionality to input
void ARunningCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunningCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARunningCharacter::StopJumping);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunningCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunningCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ARunningCharacter::MoveDown);
}

void ARunningCharacter::ChangeLaneUpdate(const float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(RunGameMode->LaneSwitchValues[CurrentLane], RunGameMode->LaneSwitchValues[NextLane], Value);
	SetActorLocation(Location);
}

void ARunningCharacter::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}

void ARunningCharacter::Death()
{
		if(!bIsDead)
	{ 

		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();

	if (World)
	{	
		bIsDead = true;

		DisableInput(nullptr);

			if (DeathParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
			}

			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}

			GetMesh()->SetVisibility(false);

			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ARunningCharacter::OnDeath, 1.f);
	}
	}
}

void ARunningCharacter::OnDeath()
{
	if (RestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
	}

	RunGameMode->PlayerDied();
}

void ARunningCharacter::ResetLevel()
{
	bIsDead = false;
	EnableInput(nullptr);
	GetMesh()->SetVisibility(true);

	if (PlayerStart)
	{
		SetActorLocation(PlayerStart->GetActorLocation());
		SetActorRotation(PlayerStart->GetActorRotation());
	}
}


void ARunningCharacter::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane +1, 0, 2);
	ChangeLane();
}

void ARunningCharacter::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane -1, 0, 2);
	ChangeLane();
}

void ARunningCharacter::MoveDown()
{
	static FVector Impulse = FVector(0, 0, MoveDownImpulse);
	GetCharacterMovement()->AddImpulse(Impulse, true);

}

