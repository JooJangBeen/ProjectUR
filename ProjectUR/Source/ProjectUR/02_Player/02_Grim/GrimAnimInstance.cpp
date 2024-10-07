// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimAnimInstance.h"
#include "GrimCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math.h"

UGrimAnimInstance::UGrimAnimInstance( const FObjectInitializer& ObjectInitializer )
	:Super( ObjectInitializer )
{
}

void UGrimAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GrimCharacter = Cast<AGrimCharacter>(TryGetPawnOwner());

	if (GrimCharacter) GrimMovementComponent = GrimCharacter->GetCharacterMovement();
}

void UGrimAnimInstance::NativeUpdateAnimation( float deltaTime )
{
	Super::NativeUpdateAnimation( deltaTime );

	if ( IsValid(GrimCharacter) && IsValid(GrimMovementComponent) )
	{
		CurSpeed = GrimCharacter->GetVelocity().Size();
		MoveAxis_X = GrimCharacter->GetMoveForwardInput() * CurSpeed;
		MoveAxis_Y = GrimCharacter->GetMoveRightInput() * CurSpeed;
		IsAccelation = GrimMovementComponent->GetCurrentAcceleration().Length() > 0.f ? true : false;
		IsInAir = GrimMovementComponent->IsFalling();
		IsTurn = GrimCharacter->GetIsTurn();

		FRotator Rot = GrimCharacter->GetBaseAimRotation() - GrimCharacter->GetActorRotation();
		AimPitch = Rot.Pitch;
		AimYaw = NormalizeYaw(Rot.Yaw);

		//FString tt = "AimPitch : " + FString::SanitizeFloat(AimPitch) + "AimYaw : " + FString::SanitizeFloat(AimYaw);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, tt);
	}
}

float UGrimAnimInstance::NormalizeYaw(float Yaw)
{
	while (Yaw > 180.0f) Yaw -= 360.0f;
	while (Yaw < -180.0f) Yaw += 360.0f;
	return Yaw;
}
