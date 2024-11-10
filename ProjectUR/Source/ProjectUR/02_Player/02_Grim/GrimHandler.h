// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrimHandler.generated.h"

UENUM(BlueprintType)
enum class EGrimNetworkType : uint8
{
	A,
	B,
	C,
	MAX
};
/**
 * 
 */
class PROJECTUR_API GrimHandler
{
public:
	GrimHandler();
	~GrimHandler();

public:
	UFUNCTION()
	virtual void ProcessNetworkPacket();

	UFUNCTION(NetMulticast, Reliable)
	void TextNetMulticast(); // 서버에서 호출되어 모든 클라이언트에서 실행
};
