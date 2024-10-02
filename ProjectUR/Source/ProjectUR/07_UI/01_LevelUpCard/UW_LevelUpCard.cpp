// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_LevelUpCard.h"
#include "../02_Player/BaseCharacter.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h" 
#include "Components/Button.h" 
#include "Math/Vector2D.h"
#include "Math/UnrealMathUtility.h" 
#include "../11_Manager/Managers.h"
#include "Engine/Texture2D.h"

void UUW_LevelUpCard::NativeConstruct()
{
	Super::NativeConstruct();
	PrepareWidget();
	BindFuction();
	SetCardContents();

}

void UUW_LevelUpCard::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUW_LevelUpCard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bIsHoverd)
	{
		HoverdTime += InDeltaTime;
		if (HoverdTime > 0.8f)
		{
			HoverdTime = 0;
		}
		else if (HoverdTime < 0.4f)
		{
			Button->SetBackgroundColor(FLinearColor::LerpUsingHSV(HoverColor, (OriginalColor + HoverColor) * 0.5f, HoverdTime * 2.5f));
		}
		else
		{
			Button->SetBackgroundColor(FLinearColor::LerpUsingHSV((OriginalColor + HoverColor) * 0.5f, HoverColor, (HoverdTime - 0.4f)* 2.5f));
		}
	}

}

void UUW_LevelUpCard::OnCardMouseEnter()
{
	bIsHoverd = true;
	HoverdTime = 0;
}

void UUW_LevelUpCard::OnCardMouseLeave()
{
	bIsHoverd = false;
	HoverdTime = 0;
	Button->SetBackgroundColor(OriginalColor);
}

void UUW_LevelUpCard::OnCardClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false; // 마우스 커서 숨기기
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}

	ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());
	check(PlayerCharacter != nullptr);

	PlayerCharacter->ImplementCard(TargetCardNum);

	GetMgr(UUIManager)->RemoveFromVieport_UserWidgetGroup("LevelUpCardUIGroup");
}

void UUW_LevelUpCard::PrepareWidget()
{
	CardName = Cast<UTextBlock>(GetWidgetFromName(FName("ItemName")));
	check(CardName != nullptr);
	CardDescription = Cast<UTextBlock>(GetWidgetFromName(FName("ItemDescription")));
	check(CardDescription != nullptr);
	CardIcon = Cast<UBorder>(GetWidgetFromName(FName("Icon")));
	check(CardIcon != nullptr);
	Button = Cast<UButton>(GetWidgetFromName(FName("BTBTBT")));
	check(Button != nullptr);
	Level = Cast<UTextBlock>(GetWidgetFromName(FName("LevelText")));
	check(Level != nullptr);
}

void UUW_LevelUpCard::BindFuction()
{
	Button->OnHovered.Clear();
	Button->OnUnhovered.Clear();
	Button->OnClicked.Clear();

	Button->OnHovered.AddDynamic(this, &UUW_LevelUpCard::OnCardMouseEnter);
	Button->OnUnhovered.AddDynamic(this, &UUW_LevelUpCard::OnCardMouseLeave);
	Button->OnClicked.AddDynamic(this, &UUW_LevelUpCard::OnCardClicked);
}

void UUW_LevelUpCard::SetCardContents()
{
	bIsHoverd = false;
	HoverdTime = 0;
	OriginalColor = FLinearColor(1.f, 1.f, 1.f, 1.f);
	HoverColor = FLinearColor(0.256723f, 1.0f, 0, 1.0f);

	Button->SetBackgroundColor(OriginalColor);

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Button->Slot);
	if (GetUIName() == FName("LevelUpCard_1"))
		CanvasSlot->SetPosition(FVector2D(-620.f, 0.f));
	else if (GetUIName() == FName("LevelUpCard_3"))
		CanvasSlot->SetPosition(FVector2D(620.f, 0.f));

	/*
		void ImplementCard(int8 index);
		const FCardData& GetCardData(int8 index);
	*/

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true; 

		FInputModeUIOnly InputMode;
		//InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}

	ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	check(PlayerCharacter != nullptr);
	TargetCardNum = FMath::RandRange(0, PlayerCharacter->GetTotalCardNum() - 1);

	CLevelUpCardData::FCardData CardData = PlayerCharacter->GetCardData(TargetCardNum);

	CardName->SetText(FText::FromString(CardData.CardName));
	CardDescription->SetText(FText::FromString(CardData.SkillCardDesc));
	Level->SetText(FText::FromString("LV : " + FString::FromInt(*CardData.CardLevel)));



	UTexture2D* NewIcon= LoadObject<UTexture2D>(nullptr, *PlayerCharacter->GetSkillIconRef(TargetCardNum));
	
	check(NewIcon != nullptr);
	CardIcon.Get()->SetBrushFromTexture(NewIcon);
	CardIcon.Get()->BrushColor = PlayerCharacter->GetSkillIconColor(TargetCardNum);

}
