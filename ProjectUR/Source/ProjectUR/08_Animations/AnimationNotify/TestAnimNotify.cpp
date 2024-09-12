// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAnimNotify.h"

void UTestAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);


	//MeshComp->GetOwner();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "AnimNotify Test Activated");

}

void UTestAnimNotify::TEST_BlueprintNativeEvent_Implementation() const
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("C++ TEST_BlueprintNativeEvent"));
}


void UTestAnimNotify::TEST_BlueprintCallable() const
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("C++ TEST_BlueprintCallable"));
}
