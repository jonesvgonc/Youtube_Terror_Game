// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"
#include "../../Public/Characters/TerrorGameFPSCharacter.h"

void UPlayerAnimInstance::SetDirectionAndSpeed()
{
	APawn* PawRef = TryGetPawnOwner();

	if (!PawRef)
		return;

	Speed = static_cast<float>(PawRef->GetVelocity().Length());

	Direction = static_cast<float>(CalculateDirection(PawRef->GetVelocity(), PawRef->GetActorRotation()));


	APlayerController* myController = GetWorld()->GetFirstPlayerController();
	if (myController)
	{
		ATerrorGameFPSCharacter* myCharacter = static_cast<ATerrorGameFPSCharacter*>(myController->GetCharacter());
		if (myCharacter)
		{
			Pitch = myCharacter->pitch;
		}
	}
}
