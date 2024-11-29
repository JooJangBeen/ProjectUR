// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTGameplayAbility.h"
#include "NarbashNormalAtkAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UNarbashNormalAtkAbility : public UCTGameplayAbility
{
	GENERATED_BODY()
	
public:
	UNarbashNormalAtkAbility();

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
    void SetupAnimNotify(const FGameplayAbilityActorInfo* OwnerInfo);

private:
    UPROPERTY()
    TObjectPtr<UAnimMontage> AbilityAnimMTG;

    int32 CurCombo;

    int32 IsAttacking;

    bool IsNextAttack;

    bool bOnce;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detail", Meta = (AllowPrivateAccess = true))
    int32 MaxCombo;

};
