// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDisplayWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

void UPlayerDisplayWidget::SetDisplayText(FString Text)
{
	if (!DisplayText) return;

	DisplayText->SetText(FText::FromString(Text));
}

void UPlayerDisplayWidget::ShowPlayerNetRole(APawn* Pawn)
{
	if (!Pawn) return;

	ENetRole localRole = Pawn->GetLocalRole();

	FString localRoleStr;
	switch (localRole)
	{
	case ENetRole::ROLE_SimulatedProxy: localRoleStr = FString("SimulatedProxy"); break;
	case ENetRole::ROLE_AutonomousProxy: localRoleStr = FString("AutonomousProxy"); break;
	case ENetRole::ROLE_Authority: localRoleStr = FString("Authority"); break;
	}

	ENetRole remoteRole = Pawn->GetRemoteRole();

	FString remoteRoleStr;
	switch (remoteRole)
	{
	case ENetRole::ROLE_SimulatedProxy: remoteRoleStr = FString("SimulatedProxy"); break;
	case ENetRole::ROLE_AutonomousProxy: remoteRoleStr = FString("AutonomousProxy"); break;
	case ENetRole::ROLE_Authority: remoteRoleStr = FString("Authority"); break;
	}

	FString ResultStr = FString::Printf(TEXT("Local : %s \n Remote: %s"), *localRoleStr, *remoteRoleStr);

	SetDisplayText(ResultStr);
}

void UPlayerDisplayWidget::SetWidgetComopnent(UWidgetComponent* InWidgetComponent)
{
	Component = InWidgetComponent;
}

void UPlayerDisplayWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	if (Component && GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
			FVector WidgetLocation = Component->GetComponentLocation();

			// 위젯이 카메라를 바라보도록 회전 설정
			FRotator LookAtRotation = (CameraLocation - WidgetLocation).Rotation();
			LookAtRotation.Pitch = 0;  // 특정 축을 고정하려면 설정 가능
			LookAtRotation.Roll = 0;

			Component->SetWorldRotation(LookAtRotation);
		}
	}
}
