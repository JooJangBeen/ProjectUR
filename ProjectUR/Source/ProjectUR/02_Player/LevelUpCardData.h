// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../09_Enums/PlayerEnum.h"
/**
 * 
 */

class PROJECTUR_API CLevelUpCardData
{
public:
	typedef void(CLevelUpCardData::* CardImplementFuction)();
	struct FCardData
	{

		FCardData() {}

		CardImplementFuction Implement;
		FString CardName;
		FString SkillCardDesc;

		FString IconRef = "";
		FString SubIconRef = "";

		int8 UseIconNum;
		int8 IconChangeLevelInterval;
		int8* CardLevel;
		FLinearColor IconColor;
	};

public:
	CLevelUpCardData();
	virtual ~CLevelUpCardData();

public:
	int8 GetTotalCardNum() { return FunctionsArray.Num(); };
	int8 GetTotalPublicCardNum() {	return TotalPublicCardNum; };
	int8 GetTotalCharacterCardNum() { return TotalCharacterCardNum; };
	const int8& GetCardLevel(int8 index) {return *FunctionsArray[index].CardLevel;};
	FString GetSkillIconRef(int8 index);
	FLinearColor GetSkillIconColor(int8 index) { return FunctionsArray[index].IconColor; };
	void ImplementCard(int8 index);
	const FCardData& GetCardData(int8 index);



protected:
	void InitializeCardData(ECharacterType	CharacterType);

	//==================================================================================
	// LevelUpCard Impelement
	//==================================================================================
protected:
#pragma region PublicCard
	virtual void PublicCardImplement_00() {};
	virtual void PublicCardImplement_01() {};
	virtual void PublicCardImplement_02() {};
	virtual void PublicCardImplement_03() {};
	virtual void PublicCardImplement_04() {};
	virtual void PublicCardImplement_05() {};
	virtual void PublicCardImplement_06() {};
	virtual void PublicCardImplement_07() {};
	virtual void PublicCardImplement_08() {};
	virtual void PublicCardImplement_09() {};
	virtual void PublicCardImplement_10() {};
	virtual void PublicCardImplement_11() {};
	virtual void PublicCardImplement_12() {};
	virtual void PublicCardImplement_13() {};
	virtual void PublicCardImplement_14() {};
	virtual void PublicCardImplement_15() {};
	virtual void PublicCardImplement_16() {};
	virtual void PublicCardImplement_17() {};
	virtual void PublicCardImplement_18() {};
	virtual void PublicCardImplement_19() {};
#pragma endregion
#pragma region CharaterCard
	virtual void CharaterCardImplement_00() {};
	virtual void CharaterCardImplement_01() {};
	virtual void CharaterCardImplement_02() {};
	virtual void CharaterCardImplement_03() {};
	virtual void CharaterCardImplement_04() {};
	virtual void CharaterCardImplement_05() {};
	virtual void CharaterCardImplement_06() {};
	virtual void CharaterCardImplement_07() {};
	virtual void CharaterCardImplement_08() {};
	virtual void CharaterCardImplement_09() {};
	virtual void CharaterCardImplement_10() {};
	virtual void CharaterCardImplement_11() {};
	virtual void CharaterCardImplement_12() {};
	virtual void CharaterCardImplement_13() {};
	virtual void CharaterCardImplement_14() {};
	virtual void CharaterCardImplement_15() {};
	virtual void CharaterCardImplement_16() {};
	virtual void CharaterCardImplement_17() {};
	virtual void CharaterCardImplement_18() {};
	virtual void CharaterCardImplement_19() {};
#pragma endregion

	//==================================================================================
	// LevelUpCard Level
	//==================================================================================
protected:
	TArray<int8> PublicCardLevel;
	TArray<int8> CharacterCardLevel;

	//==================================================================================
	// Valiable
	//==================================================================================
protected:
	TArray<FCardData> FunctionsArray;
	TArray<UDataTable*> CardDTArray;
	int8 TotalPublicCardNum = 0;
	int8 TotalCharacterCardNum = 0;

private:
	FString ModifyTexturePath(const FString& OriginalPath, int8 UseIconNum, FCardData& CardData);
};
