// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingEffect.h"
#include "../01_AttributeSet/PlayerAttributeSet.h"

UHealingEffect::UHealingEffect()
{
    /* DurationPolicy : 효과 적용 방식
       
       1) EGameplayEffectDurationType
            - Instant           : 즉시 적용
            - HasDuration       : 지속시간
            - Infinite          : 수동으로 제거될 때 까지 무한
       
       2)DurationMagnitude = FScalableFloat(5.0f); // 지속시간을 5초로 설정

        // 간격 설정 (예: 1초마다 효과 적용)
        Period = FScalableFloat(1.0f); // 1초 간격으로 효과 적용
    */ 
    DurationPolicy = EGameplayEffectDurationType::HasDuration;

    /* DurationMagnitude : 효과의 지속시간 설정
       - DurationPolicy 값이 HasDuration인 경우 동작
       - DurationPolicy 값이 Infinite인 경우 0.f로 설정
       - FScalableFloat : 값을 동적 수정할 수 있게 유연하게 관리 해주는 구조체
    */
    DurationMagnitude = FScalableFloat(5.f);
    
    /* Period  : 수행 간격 (second 단위)
        - DurationPolicy 값이 HasDuration, Infinite인 경우 동작
        - FScalableFloat : 값을 동적 수정할 수 있게 유연하게 관리 해주는 구조체
    */
    Period = FScalableFloat(1.0f);

    /* FGameplayModifierInfo(수정자) : 캐릭터의 속성(Attribute)값을 변경
    
       1) Attribute
            - 변경하려는 속성에 대한 참조를 가져옴 (메모리 위치)

       2) ModifierOp
            - 값을 수정하는 방식을 정의
            - EGameplayModOp::Additive          : 더하기
            - EGameplayModOp::Multiplicitive    : 곱하기
            - EGameplayModOp::Override          : 값을 덮어쓴다.
            - EGameplayModOp::Division          : 나누기

       3) ModifierMagnitude
            - 적용할 수치
            - FScalableFloat : 값을 동적 수정할 수 있게 유연하게 관리 해주는 구조체

    */ 
    FGameplayModifierInfo HealthModifier;
    HealthModifier.Attribute = UPlayerAttributeSet::GetCurrentHpAttribute();
    HealthModifier.ModifierOp = EGameplayModOp::Additive;
    HealthModifier.ModifierMagnitude = FScalableFloat(50.f);
    
    /*
        수정자를 GameplayEffect에 추가
        - 여러개의 수정자를 Add 시켜 속성 값에 변경을 일으킬 수 있다.
    */ 
    Modifiers.Add(HealthModifier);

}
