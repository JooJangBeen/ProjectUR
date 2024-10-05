// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CTUserWidget.h"
#include "UW_Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UUW_Crosshair : public UCTUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;


public:
	void SetMainCrosshairIcon(FString ref);
	void SetMainColor(FLinearColor color);
	void ResetMainColor();

public:
	UPROPERTY()
	TObjectPtr<class UImage> pMainCrosshair;
	UPROPERTY()
	TObjectPtr<class UImage> pSubCrosshair;

private:
	TObjectPtr<UTexture2D> OrigMainIcon;
	FLinearColor OrigMainColor;
};
