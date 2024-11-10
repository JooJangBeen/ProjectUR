// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{

}

void UPlayerAttributeSet::SetHp(float maxHp, float curHp)
{
	Hp.SetBaseValue(maxHp);
	Hp.SetCurrentValue(curHp);

}

void UPlayerAttributeSet::SetMaxHp(float value)
{
	Hp.SetBaseValue(value);

}

void UPlayerAttributeSet::SetCurrentHp(float value)
{
	Hp.SetCurrentValue(value);

}

float UPlayerAttributeSet::GetCurrentHp()
{
	return Hp.GetCurrentValue();

}

float UPlayerAttributeSet::GetMaxHp()
{
	return Hp.GetBaseValue();

}
