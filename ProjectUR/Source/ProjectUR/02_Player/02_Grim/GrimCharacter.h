// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimHandler.h"
#include "../BaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "../05_GAS/01_AttributeSet/PlayerAttributeSet.h"
#include "GrimCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API AGrimCharacter : public ABaseCharacter, public GrimHandler
{
	GENERATED_BODY()

public:
	AGrimCharacter();

//=====================================================================================
// Default Override Fuction
//=====================================================================================
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

//=====================================================================================
// GameAttributeSystem
//=====================================================================================
public:
	UPlayerAttributeSet* GrimAttribute;

//=====================================================================================
// Dedicated Server
//=====================================================================================
public:
	UPROPERTY(ReplicatedUsing = OnRep_ProcessNetworkPacket)
	EGrimNetworkType ENetworkType = EGrimNetworkType::MAX;

	UPROPERTY(Replicated)
	int32 MyVariable;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	void OnRep_ProcessNetworkPacket();

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC(); // 서버에서 호출되어 모든 클라이언트에서 실행

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC(); //클라이언트에서 서버로 실행, 해킹의 위험이 있기에 WithValidation 플래그를 추가하여 추가 검증 가능

	UFUNCTION(Client, Reliable)
	void ClientRPC(); // 서버에서 호출되어 특정 클라이언트에서 실행

//=====================================================================================
// Load & Prepare Something
//=====================================================================================
void SetupDefault();
void LoadMeshAnimation();
void LoadEnhancedInput();
void BindInputAction2Fuction(UInputComponent* PlayerInputComponent);

//=====================================================================================
// Input
//=====================================================================================
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void LeftButton(const FInputActionValue& Value);
	void RightButton(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> LeftButtonAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> RightButtonAction;

//=====================================================================================
// For Animation Control
//=====================================================================================
public:
	float GetMoveForwardInput() { return MoveForwardInput; };
	float GetMoveRightInput() { return MoveRightInput; };
	bool  GetIsTurn() { return bIsTurn; };

	float NormalizeYaw(float Yaw);
	float CalculateYaw(float DestYaw, float SourYaw);

private:
	FVector2D OldDirVector;

	float MoveForwardInput;
	float MoveRightInput;

	bool IsAttacking;
	bool bPressAttack;
	bool bIsTurn;
};
