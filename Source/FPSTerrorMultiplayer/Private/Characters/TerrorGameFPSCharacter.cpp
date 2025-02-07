// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TerrorGameFPSCharacter.h"

// Sets default values
ATerrorGameFPSCharacter::ATerrorGameFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATerrorGameFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrorGameFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATerrorGameFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

