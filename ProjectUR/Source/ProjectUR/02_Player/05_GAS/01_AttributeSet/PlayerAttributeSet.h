// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "../CTAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTUR_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UPlayerAttributeSet();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", Meta = (AllowPrivateAccess = true))
    FGameplayAttributeData CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHp;

public:
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentHp)
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHp)

//=====================================================================================
// Dedicated Server
//=====================================================================================
public:
    UFUNCTION()
    void OnRep_Damage(const FGameplayAttributeData& OldDamage);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage)
    FGameplayAttributeData Damage;
    //ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Damage)

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
















//public:
//    /*
//        FindFieldChecked : 클래스 내에서 속성을 찾는다.
//        GET_MEMBER_NAME_CHECKED : 클래스의 멤버 변수를 안전하게 가져온다, 존재하지 않을 시 컴파일 에러
//        FProperty : 속성 값의 기본 클래스 (정수, 실수 등의 기본 클래스)
//        FGameplayAttribute : 게임 내에서 속성 값의 추가, 변경, 삭제하는 등의 작업을 수행하는 데 필요한 메소드를 제공, FProperty의 포인터를 통해 속성을 참조
//    */
//    UFUNCTION()
//    static FGameplayAttribute GetHpAttribute() { return FGameplayAttribute(FindFieldChecked<FProperty>(UPlayerAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPlayerAttributeSet, Hp))); }