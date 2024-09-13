// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PCNarbash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API APCNarbash : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APCNarbash();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetupNotifys();
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	virtual void StopJumping() override;

	void NormalAttack();

private:
	void InitMappingContextSetting();

public:
	float GetMoveForwardInput();
	float GetMoveRightInput();

private:
	/* Relate Key Bind */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> NormalAttackAction;

private:
	float MoveForwardInput;
	float MoveRightInput;

	bool IsAttacking;
	bool bPressAttack;

private:
	/* Relate Player State / if state class is implemented, move data */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player State", Meta = (AllowPrivateAccess = true))
	uint8 MaxCombo;
	
	uint8 CurCombo;
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPCNarbashAnimInstance> PCAnimInstance;

};
