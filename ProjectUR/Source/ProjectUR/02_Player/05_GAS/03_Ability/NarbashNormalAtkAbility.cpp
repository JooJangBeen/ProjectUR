// Fill out your copyright notice in the Description page of Project Settings.


#include "NarbashNormalAtkAbility.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "../02_Player/04_Narbash/PCNarbash.h"
#include "../02_Player/04_Narbash/PCNarbashAnimInstance.h"
#include "AbilitySystemComponent.h"

UNarbashNormalAtkAbility::UNarbashNormalAtkAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    AbilityAnimMTG = LoadObject<UAnimMontage>(this, TEXT("/Game/02_Player/04_PCNarbash/01_Animations/MTG_PCNarbashNormalATK.MTG_PCNarbashNormalATK"));

    IsNextAttack = false;
    bOnce = false;
    MaxCombo = 3;

}

void UNarbashNormalAtkAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

    TObjectPtr<ACharacter> Character = Cast<ACharacter>(OwnerInfo->AvatarActor);
    
    if (!bOnce)
    {
        SetupAnimNotify(OwnerInfo);
    }

    if (!Character)
    {
        UE_LOG(LogTemp, Error, TEXT("UNarbashNormalAtkAbility::ActivateAbility : Not Exist PlayerCharacter"));
    }

    if (!IsAttacking)
    {
        Character->PlayAnimMontage(AbilityAnimMTG);
        IsAttacking = true;
    }
    else
    {
        IsNextAttack = true;
    }
    
    EndAbility(Handle, OwnerInfo, ActivationInfo, false, false);

}

void UNarbashNormalAtkAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, OwnerInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UNarbashNormalAtkAbility::SetupAnimNotify(const FGameplayAbilityActorInfo* OwnerInfo)
{
    TObjectPtr<ACharacter> Character = Cast<ACharacter>(OwnerInfo->AvatarActor);

    Cast<APCNarbash>(Character)->GetAnimInstance()->OnAttackEnd.AddLambda([this]()->void {
        IsAttacking = false;
        IsNextAttack = false;
        CurCombo = 0;
    });

    Cast<APCNarbash>(Character)->GetAnimInstance()->OnNextComboCheck.AddLambda([this]()->void {
        if (IsNextAttack)
        {
            CurCombo = (CurCombo + 1) % MaxCombo;
            IsNextAttack = false;
            Cast<UPCNarbashAnimInstance>(CurrentActorInfo->GetAnimInstance())->PlayNormalAttackMontage(CurCombo);
        }
    });
    bOnce = true;

}
