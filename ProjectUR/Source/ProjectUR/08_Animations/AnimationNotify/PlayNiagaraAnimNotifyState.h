// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PlayNiagaraAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UPlayNiagaraAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = ture))
	TObjectPtr<class UNiagaraSystem> NiagaraSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = ture))
	TObjectPtr<class UNiagaraComponent> CreatedNiagaraComponents;

};
