// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CTUserWidget.h"
#include "UW_LevelUpCard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UUW_LevelUpCard : public UCTUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	//////////////////////////////////////////
	/// 콜백 이벤트함수에 바인딩할 함수
	//////////////////////////////////////////
private:
	UFUNCTION()
	void OnCardMouseEnter();
	UFUNCTION()
	void OnCardMouseLeave();
	UFUNCTION()
	void OnCardClicked();
	//////////////////////////////////////////
	/// 위젯
	//////////////////////////////////////////
private:
	UPROPERTY()
	TObjectPtr<class UTextBlock> CardName;
	UPROPERTY()
	TObjectPtr<class UTextBlock> CardDescription;
	UPROPERTY()
	TObjectPtr<class UBorder> CardIcon;
	UPROPERTY()
	TObjectPtr<class UButton> Button;
	UPROPERTY()
	TObjectPtr<class UTextBlock> Level;
	
private:
	void PrepareWidget();
	void BindFuction();
	void SetCardContents();

private:
	int8 TargetCardNum;
	bool bIsHoverd;
	float HoverdTime;
	FLinearColor OriginalColor;
	FLinearColor HoverColor;
};
