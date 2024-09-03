// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManager.generated.h"

class UUserWidget;
class UWidget;

/**
 * 
 */
UCLASS()
class PROJECTUR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

public:
	// 플레이어 초기 UI 생성 및 연동
	void InitializeUI();

	// Get UI
	UWidget* GetWidgetFromName(FName wigetName);

private:
	UPROPERTY()
	UUserWidget* mPlayerMainUI;

};
