// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSTERRORMULTIPLAYER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation-Variables", meta = (AllowPrivateAccess = "true"))
	float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation-Variables", meta = (AllowPrivateAccess = "true"))
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation-Variables", meta = (AllowPrivateAccess = "true"))
	float Pitch;

public:
	UFUNCTION(BlueprintCallable)
	void SetDirectionAndSpeed();
	
};
