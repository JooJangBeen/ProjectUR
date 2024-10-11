// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GrimAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UGrimAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UGrimAnimInstance( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation( float deltaTime ) override;

public:
	float NormalizeYaw(float Yaw);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TObjectPtr<class AGrimCharacter> GrimCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCharacterMovementComponent> GrimMovementComponent;

#pragma region PlayerInfoValue
private:
	/* Player Info Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float MoveAxis_X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float MoveAxis_Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsAccelation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	int JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float CurSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimYaw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimPitch;
#pragma endregion
};
