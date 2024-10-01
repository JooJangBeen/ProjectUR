// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UCTUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FName GetUIGroupName() { return UIGroupName; };
	FName GetUIName() { return UIName; };
	void SetUIGroupName(FName Name) { UIGroupName = Name; };
	void SetUIName(FName Name) { UIName = Name; };

private:
	FName UIGroupName;
	FName UIName;
};
