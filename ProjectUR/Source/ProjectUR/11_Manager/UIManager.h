// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Components/SlateWrapperTypes.h"
#include "UIManager.generated.h"

class UCTUserWidget;
class UWidget;

/**
 * 
 */
UCLASS()
class PROJECTUR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

	////////////////////////////////////////////////////////////////////////////////
	//Initialize에서 UI Group에 대한 키값 및 Ref를 미리 생성
	////////////////////////////////////////////////////////////////////////////////
protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	////////////////////////////////////////////////////////////////////////////////
	// UI 생성 및 제거
	////////////////////////////////////////////////////////////////////////////////
public:
	void AddToViewPort_UserWidgetGroup(FName&& UIGroupName);
	void AddToViewPort_UserWidget(FName&& WidgetName);
	void RemoveFromVieport_UserWidgetGroup(FName&& UIGroupName);
	void RemoveFromVieport_UserWidget(FName&& WidgetName);
	void TurnAddRemove_UserWidgetGroup(FName&& UIGroupName);
	void TurnAddRemove_UserWidget(FName&& WidgetName);


	////////////////////////////////////////////////////////////////////////////////
	// For UserWidget
	////////////////////////////////////////////////////////////////////////////////
public:
	TObjectPtr<UCTUserWidget> const GetUserWidget(FName&& UserWidgetName);
	void SetVisibility_UserWidget(FName&& UserWidgetName, ESlateVisibility EVisibility);
	void OnOffVisibility_UserWidget(FName&& UserWidgetName);

	////////////////////////////////////////////////////////////////////////////////
	// For Widget
	////////////////////////////////////////////////////////////////////////////////
public:
	TObjectPtr<UWidget> const GetWidget(FName UserWidgetName, FName wigetName);


private:
	void PrepareUserWidget();

private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UCTUserWidget>> Widgets;
	TMap<FName, TMap<FName,FString>> UIGroupReference;

};
