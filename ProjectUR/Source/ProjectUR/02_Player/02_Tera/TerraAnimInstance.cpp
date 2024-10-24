// Fill out your copyright notice in the Description page of Project Settings.


#include "TerraAnimInstance.h"
#include "TeraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math.h"

UTerraAnimInstance::UTerraAnimInstance()
{
	IsAccelation = false;
	IsInAir = false;
}

void UTerraAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	TObjectPtr<ATeraCharacter> Owner = Cast<ATeraCharacter>(TryGetPawnOwner());


	if (::IsValid(Owner))
	{
		CurSpeed = Owner->GetVelocity().Size();
		MoveAxis_X = Owner->GetMoveForwardInput() * CurSpeed;
		MoveAxis_Y = Owner->GetMoveRightInput() * CurSpeed;
		IsAccelation = (Owner->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f ? true : false);
		IsInAir = Owner->GetCharacterMovement()->IsFalling();
		JumpCount = Owner->GetJumpCount();
		IsTurn = Owner->GetIsTurn();

		FRotator Rot = Owner->GetBaseAimRotation() - Owner->GetActorRotation();
		AimPitch = Rot.Pitch;
		AimYaw = NormalizeYaw(Rot.Yaw);

		//FString tt = "AimPitch : " + FString::SanitizeFloat(AimPitch) + "AimYaw : " + FString::SanitizeFloat(AimYaw);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, tt);
	}
}

float UTerraAnimInstance::NormalizeYaw(float Yaw)
{
	while (Yaw > 180.0f) Yaw -= 360.0f;
	while (Yaw < -180.0f) Yaw += 360.0f;
	return Yaw;
}
