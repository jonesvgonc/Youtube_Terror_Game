// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TerrorGameFPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ATerrorGameFPSCharacter::ATerrorGameFPSCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	 	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FlashLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashLight"));

	FlashLight->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("hand_rSocket")));
}

// Called when the game starts or when spawned
void ATerrorGameFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}

void ATerrorGameFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		if (MovementVector.X != 0 || MovementVector.Y < 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = 150.f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 250.f;
		}


		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATerrorGameFPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);

		AddControllerPitchInput(LookAxisVector.Y);

		SetFlashLightRotation(LookAxisVector.Y);

		FRotator rot = Controller->GetControlRotation();
		PlayerCameraManager->LimitViewPitch(rot, MinPitch, MaxPitch);

		Controller->SetControlRotation(rot);
	}
}

// Called every frame
void ATerrorGameFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrorGameFPSCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ATerrorGameFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{		

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATerrorGameFPSCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATerrorGameFPSCharacter::Look);
	}

}

void ATerrorGameFPSCharacter::SetFlashLightRotation(float rotValue)
{
	pitch += (-1 * rotValue);
	if (pitch > 72.f)
	{
		pitch = 72.f;
	}
	else if (pitch < 0.f)
	{
		pitch = 0.f;
	}
}

