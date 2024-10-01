// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "../07_UI/CTUserWidget.h"
#include "Components/Widget.h"

void UUIManager::Initialize(FSubsystemCollectionBase& collection)
{
	TMap<FName, FString> LevelUpCardUI;
	LevelUpCardUI.Add("LevelUpCard_1", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/04_UI/01_LevelUpCard/LevelUpCard.LevelUpCard_C'"));
	LevelUpCardUI.Add("LevelUpCard_2", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/04_UI/01_LevelUpCard/LevelUpCard.LevelUpCard_C'"));
	LevelUpCardUI.Add("LevelUpCard_3", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/04_UI/01_LevelUpCard/LevelUpCard.LevelUpCard_C'"));
	UIGroupReference.Add("LevelUpCardUIGroup", LevelUpCardUI);


	PrepareUserWidget();
}

void UUIManager::AddToViewPort_UserWidgetGroup(FName UIGroupName)
{
	TMap<FName, FString>* UIGroupRef = UIGroupReference.Find(UIGroupName);
	check(UIGroupRef != nullptr);

	for (auto& Ref : *UIGroupRef)
	{
		TObjectPtr<UCTUserWidget>* widget = Widgets.Find(Ref.Key);
		check(widget && *widget);

		widget->Get()->AddToViewport();
	}

}

void UUIManager::AddToViewPort_UserWidget(FName WidgetName)
{
	TObjectPtr<UCTUserWidget>* widget = Widgets.Find(WidgetName);
	check(widget && *widget);

	widget->Get()->AddToViewport();
}

void UUIManager::RemoveFromVieport_UserWidgetGroup(FName UIGroupName)
{
	TMap<FName, FString>* UIGroupRef = UIGroupReference.Find(UIGroupName);
	check(UIGroupRef != nullptr);

	for (auto& Ref : *UIGroupRef)
	{
		TObjectPtr<UCTUserWidget>* widget = Widgets.Find(Ref.Key);
		check(widget && *widget);

		widget->Get()->RemoveFromViewport();
	}
}

void UUIManager::RemoveFromVieport_UserWidget(FName WidgetName)
{
	TObjectPtr<UCTUserWidget>* widget = Widgets.Find(WidgetName);
	check(widget && *widget);

	widget->Get()->RemoveFromViewport();
}

void UUIManager::TurnAddRemove_UserWidgetGroup(FName UIGroupName)
{
	TMap<FName, FString>* UIGroupRef = UIGroupReference.Find(UIGroupName);
	check(UIGroupRef != nullptr);

	for (auto& Ref : *UIGroupRef)
	{
		TObjectPtr<UCTUserWidget>* widget = Widgets.Find(Ref.Key);
		check(widget && *widget);

		if (widget->Get()->IsInViewport())
			widget->Get()->RemoveFromViewport();
		else
			widget->Get()->AddToViewport();
	}

}

void UUIManager::TurnAddRemove_UserWidget(FName WidgetName)
{
	TObjectPtr<UCTUserWidget>* widget = Widgets.Find(WidgetName);
	check(widget && *widget);


}




TObjectPtr<UWidget> const UUIManager::GetWidget(FName UserWidgetName, FName wigetName)
{
	TObjectPtr<UCTUserWidget>* FoundWidgetPtr = Widgets.Find(UserWidgetName);
	check(FoundWidgetPtr&&*FoundWidgetPtr);

	UWidget* Result = FoundWidgetPtr->Get()->GetWidgetFromName(wigetName);
	check(Result != nullptr);

	return TObjectPtr<UWidget>(Result);
}

void UUIManager::PrepareUserWidget()
{
	for (auto& UIGroup : UIGroupReference)
	{
		for (auto& pair : UIGroup.Value)
		{
			UClass* WidgetClass = LoadClass<UCTUserWidget>(nullptr, *pair.Value);
			check(WidgetClass != nullptr);

			UCTUserWidget* RawWidget = CreateWidget<UCTUserWidget>(GetWorld(), WidgetClass);
			check(RawWidget != nullptr);

			Widgets.Add(pair.Key, TObjectPtr<UCTUserWidget>(RawWidget));
			RawWidget->SetUIGroupName(UIGroup.Key);
			RawWidget->SetUIName(pair.Key);
		}

	}

}

TObjectPtr<UCTUserWidget> const UUIManager::GetUserWidget(FName UserWidgetName)
{
	TObjectPtr<UCTUserWidget>* FoundWidgetPtr = Widgets.Find(UserWidgetName);
	check(FoundWidgetPtr && *FoundWidgetPtr);

	return *FoundWidgetPtr;
}

void UUIManager::SetVisibility_UserWidget(FName UserWidgetName, ESlateVisibility EVisibility)
{
	TObjectPtr<UCTUserWidget>* FoundWidgetPtr = Widgets.Find(UserWidgetName);
	if (!(FoundWidgetPtr && *FoundWidgetPtr))
	{
		FString ErrMsg = "Error SetUserWidgetVisibility " + UserWidgetName.ToString() + "UI";
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrMsg);
		return;
	}

	FoundWidgetPtr->Get()->SetVisibility(EVisibility);
}

void UUIManager::OnOffVisibility_UserWidget(FName UserWidgetName)
{
	TObjectPtr<UCTUserWidget>* FoundWidgetPtr = Widgets.Find(UserWidgetName);
	if (!(FoundWidgetPtr && *FoundWidgetPtr))
	{
		FString ErrMsg = "Error SetUserWidgetVisibility " + UserWidgetName.ToString() + "UI";
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrMsg);
		return;
	}


	if (ESlateVisibility::Visible == FoundWidgetPtr->Get()->GetVisibility())
		FoundWidgetPtr->Get()->SetVisibility(ESlateVisibility::Hidden);
	else
		FoundWidgetPtr->Get()->SetVisibility(ESlateVisibility::Visible);

}

