// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseAIController.h"
#include "Perception/AIPerceptionComponent.h" // Perception 관련 헤더 추가
#include "SpiderEyeAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API ASpiderEyeAIController : public ABaseAIController
{
	GENERATED_BODY()

public:
	ASpiderEyeAIController();

public:
	void Tick(float DeltaTime)override;

	AActor* testaaa;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///For Perception
////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	// IGenericTeamAgentInterface 구현
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override; // 팀 관계 판단 함수

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	void InitializePercetion();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* iiiiPerceptionComponent;
};
