// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderEyeAIController.h"
#include "Perception/AISenseConfig_Sight.h"   // 시각 감각 설정 헤더
#include "Perception/AISenseConfig_Hearing.h" // 청각 감각 설정 헤더
#include "Perception/AISenseConfig_Damage.h"  // 데미지 감각 설정 헤더
#include "Perception/AISenseConfig_Prediction.h" // 예측 감각 설정 헤더
#include "Perception/AISense_Prediction.h"


ASpiderEyeAIController::ASpiderEyeAIController()
{
	InitializePercetion();

	testaaa = nullptr;
}

void ASpiderEyeAIController::Tick(float DeltaTime)
{
	if (testaaa)
	{
		MoveToActor(testaaa);
	}
}


ETeamAttitude::Type ASpiderEyeAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// Other 액터가 IGenericTeamAgentInterface를 구현하고 있는지 확인
	const IGenericTeamAgentInterface* TeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	if (TeamAgent)
	{
		// 대상의 팀 ID와 현재 액터의 팀 ID를 비교
		FGenericTeamId OtherTeamId = TeamAgent->GetGenericTeamId();

		if (OtherTeamId == GetGenericTeamId())
		{
			return ETeamAttitude::Friendly; // 같은 팀이면 우호적
		}
		else if (OtherTeamId == FGenericTeamId::NoTeam)
		{
			return ETeamAttitude::Neutral; // 팀이 설정되지 않았다면 중립
		}
		else
		{
			return ETeamAttitude::Hostile; // 다른 팀이면 적대적
		}
	}

	return ETeamAttitude::Neutral;
}

void ASpiderEyeAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//UpdatedActors의 분류 방식은 2가지


	//탐지된 엑터들을 if else문으로 구분하여 처리할 수 있고 인지 된 감각의 우선순위를 정할 수 있음
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor)
		{
			FActorPerceptionBlueprintInfo Info;
			PerceptionComponent->GetActorsPerception(Actor, Info);

			for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
			{
				// 감각의 타입에 따라 분류
				TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);

				if (SenseClass == UAISense_Sight::StaticClass())
				{
					// 시각에 의해 감지된 액터에 대한 동작 처리
					if (Stimulus.WasSuccessfullySensed())
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s 감지됨: 시각"), *Actor->GetName()));
						testaaa = Actor;
					}
				}
				else if (SenseClass == UAISense_Hearing::StaticClass())
				{
					// 청각에 의해 감지된 액터에 대한 동작 처리
					if (Stimulus.WasSuccessfullySensed())
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s 감지됨: 청각"), *Actor->GetName()));
					}
				}
				else if (SenseClass == UAISense_Damage::StaticClass())
				{
					// 데미지에 의해 감지된 액터에 대한 동작 처리
					if (Stimulus.WasSuccessfullySensed())
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s 감지됨: 데미지"), *Actor->GetName()));
					}
				}
				else if (SenseClass == UAISense_Prediction::StaticClass())
				{
					// 예측에 의해 감지된 액터에 대한 동작 처리
					if (Stimulus.WasSuccessfullySensed())
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s 감지됨: 예측"), *Actor->GetName()));
					}
				}
			}
		}
	}




	//인지된 엑터들을 묶어서 처리할 수 도 있으나 만약 시야나 청각 둘다 탐지가 되면 SightActors랑 HearingActors둘다 포함되서 중복 처리에대한 예외처리를 해줘야함
	/*
	TArray<AActor*> SightActors;
	TArray<AActor*> HearingActors;
	TArray<AActor*> DamageActors;
	TArray<AActor*> PredictionActors;

	if (PerceptionComponent)
	{
		// 각 감각별로 인지한 엑터 분류
		PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SightActors);
		PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), HearingActors);
		PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), DamageActors);
		PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Prediction::StaticClass(), PredictionActors);
	}

	// 시각을 통해 감지한 액터에 대한 처리 로직
	if (SightActors.Num() > 0)
	{
		for (AActor* Actor : SightActors)
		{
			if (Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Sight Detected Actor: %s"), *Actor->GetName());
			}
		}
	}

	// 청각을 통해 감지한 액터에 대한 처리 로직
	if (HearingActors.Num() > 0)
	{
		for (AActor* Actor : HearingActors)
		{
			if (Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hearing Detected Actor: %s"), *Actor->GetName());
			}
		}
	}

	// 데미지를 통해 감지한 액터에 대한 처리 로직
	if (DamageActors.Num() > 0)
	{
		for (AActor* Actor : DamageActors)
		{
			if (Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Damage Detected Actor: %s"), *Actor->GetName());
			}
		}
	}

	// 예측을 통해 감지한 액터에 대한 처리 로직
	if (PredictionActors.Num() > 0)
	{
		for (AActor* Actor : PredictionActors)
		{
			if (Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Prediction Detected Actor: %s"), *Actor->GetName());
			}
		}
	}
	*/
}

void ASpiderEyeAIController::InitializePercetion()
{

	// PerceptionComponent 생성 및 초기화
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*PerceptionComponent);

	

	//퍼셉션 컴포넌트가 객체를 인지했을 때 호출되는 함수를 바인딩
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ASpiderEyeAIController::OnPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));  // 2번 팀으로 설정

	// 시각 감각 설정
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = 1200.0f;
		SightConfig->PeripheralVisionAngleDegrees = 45.0f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true; // 적군 탐지 설정
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true; // 중립군 탐지 설정
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true; // 아군 탐지 설정

		SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;

		PerceptionComponent->ConfigureSense(*SightConfig);
		PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	}

	// 청각 감각 설정
	UAISenseConfig_Hearing* HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	if (HearingConfig)
	{
		HearingConfig->HearingRange = 1500.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

		PerceptionComponent->ConfigureSense(*HearingConfig);
	}

	// 데미지 감각 설정
	UAISenseConfig_Damage* DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	if (DamageConfig)
	{
		PerceptionComponent->ConfigureSense(*DamageConfig);
	}

	// 예측 감각 설정
	UAISenseConfig_Prediction* PredictionConfig = CreateDefaultSubobject<UAISenseConfig_Prediction>(TEXT("PredictionConfig"));
	if (PredictionConfig)
	{
		PerceptionComponent->ConfigureSense(*PredictionConfig);
	}

	// Dominant Sense 설정
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

}
