// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Crosshair.h"    
#include "Components/Image.h"   

void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();


	pMainCrosshair = Cast<UImage>(GetWidgetFromName(FName("MainCrosshair")));
	check(pMainCrosshair != nullptr);

	pSubCrosshair = Cast<UImage>(GetWidgetFromName(FName("SubCrosshair")));
	check(pSubCrosshair != nullptr);

	OrigMainIcon = Cast<UTexture2D>(pMainCrosshair->GetBrush().GetResourceObject());
	check(OrigMainIcon != nullptr);
	OrigMainColor = pMainCrosshair->Brush.TintColor.GetSpecifiedColor();

	OrigMainIcon = Cast<UTexture2D>(pMainCrosshair->GetBrush().GetResourceObject());
	check(OrigMainIcon != nullptr);

}

void UUW_Crosshair::SetMainCrosshairIcon(FString ref)
{
}

void UUW_Crosshair::SetMainColor(FLinearColor color)
{
	pMainCrosshair->Brush.TintColor = color;
}

void UUW_Crosshair::ResetMainColor()
{
	pMainCrosshair->Brush.TintColor = OrigMainColor;
}
