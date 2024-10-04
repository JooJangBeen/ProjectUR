// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayNiagaraAnimNotifyState.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

void UPlayNiagaraAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (NiagaraSystem && MeshComp)
    {
        CreatedNiagaraComponents = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraSystem, MeshComp, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true, true);
    }

}

void UPlayNiagaraAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (NiagaraSystem && MeshComp)
    {
        CreatedNiagaraComponents->Deactivate();
    }

}
