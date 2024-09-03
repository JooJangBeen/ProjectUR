// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"

void UUIManager::Initialize(FSubsystemCollectionBase& collection)
{
	mPlayerMainUI = nullptr;

}

void UUIManager::InitializeUI()
{
	if (nullptr != mPlayerMainUI)
	{
		UE_LOG(LogTemp, Error, TEXT("Already Exist Player Main UI"));
		return;
	}
	
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/04_UI/WBP_PlayerMainUI.WBP_PlayerMainUI_C'"));
	if (nullptr != WidgetClass)
	{
		mPlayerMainUI = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	}
	mPlayerMainUI->AddToViewport();

}

UWidget* UUIManager::GetWidgetFromName(FName wigetName)
{
	UWidget* Result = mPlayerMainUI->GetWidgetFromName(wigetName);

	if (nullptr == Result)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Exist Widget Name to Player Main UI"));
	}

	return Result;

}
