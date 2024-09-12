// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TestAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UTestAnimNotify : public UAnimNotify
{
	GENERATED_BODY()


	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	

public:
	//BlueprintNativeEvent -> Blueprint로 제정의 하면 Blueprint함수를 사용 재정의 하지 않으면 c++ 함수를 사용
	//Cpp랑 .h 파일 함수 명이 다름
	UFUNCTION(BlueprintNativeEvent)
	void TEST_BlueprintNativeEvent() const;

	//BlueprintImplementableEvent -> 오직 blueprint로 정의한 함수만 호출
	//함수를 따로 정의할 필요 X
	UFUNCTION(BlueprintImplementableEvent)
	void TEST_BlueprintImplementableEvent()const;

	//BlueprintImplementableEvent -> 오직 C++로 정의한 함수만 호출
	UFUNCTION(BlueprintCallable)
	void TEST_BlueprintCallable()const;
	
};
