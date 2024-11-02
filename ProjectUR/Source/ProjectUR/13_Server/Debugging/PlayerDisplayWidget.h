// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UPlayerDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayText(FString Text);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* Pawn);

	void SetWidgetComopnent(class UWidgetComponent* InWidgetComponent);

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DisplayText;

	class UWidgetComponent* Component;

	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
};
