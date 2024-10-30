// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "../13_Server/Debugging/PlayerDisplayWidget.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = PLAYERDEFAULTCAMLENTH;
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeLocation(PLAYERDEFAULTCAMPOS);
	FollowCamera->bUsePawnControlRotation = false;

	CraetePlayerDisplay();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(0);
	GetMesh()->SetRenderCustomDepth(true);

	PlayerDisplayVisibility();
}

void ABaseCharacter::CraetePlayerDisplay()
{
	PlayerDisplay = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerDisplayWidget"));
	if (PlayerDisplay)
	{
		PlayerDisplay->SetupAttachment(RootComponent);
		PlayerDisplay->SetWidgetSpace(EWidgetSpace::World);
		PlayerDisplay->SetDrawSize(FVector2D(300, 200));
		PlayerDisplay->SetRelativeLocation(FVector(0, 0, 200));

		static ConstructorHelpers::FClassFinder<UUserWidget> displayWidet(TEXT("/Game/08_Server/WBP_PlayerDisplay.WBP_PlayerDisplay_C"));

		if (displayWidet.Succeeded())
		{
			PlayerDisplay->SetWidgetClass(displayWidet.Class);
		}
	}
}

void ABaseCharacter::PlayerDisplayVisibility()
{
	if (PlayerDisplay)
	{
		PlayerDisplay->SetVisibility(true);

		UUserWidget* userWidget = Cast<UUserWidget>(PlayerDisplay->GetUserWidgetObject());
		if (userWidget)
		{
			if (UPlayerDisplayWidget* playerDisplayWidget = Cast<UPlayerDisplayWidget>(userWidget))
			{
				playerDisplayWidget->ShowPlayerNetRole(this);
				playerDisplayWidget->SetWidgetComopnent(PlayerDisplay);
			}
		}
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


