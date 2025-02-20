// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"

void UPlayerAnimInstance::SetDirectionAndSpeed()
{
	APawn* PawRef = TryGetPawnOwner();

	if (!PawRef)
		return;

	Speed = static_cast<float>(PawRef->GetVelocity().Length());

	Direction = static_cast<float>(CalculateDirection(PawRef->GetVelocity(), PawRef->GetActorRotation()));
}
