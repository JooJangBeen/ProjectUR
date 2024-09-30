// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpCardData.h"
#include "../14_Data/FLevelUpCard_Public_Card.h"
#include "../14_Data/FLevelUpCard_Kallari.h"
#include "../14_Data/FLevelUpCard_Grim.h"
#include "../14_Data/FLevelUpCard_Narbash.h"
#include "../14_Data/FLevelUpCard_Terra.h"



CLevelUpCardData::CLevelUpCardData()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PublicCardDatatable(TEXT("/Game/Data/Table/DT_LevelUpCard_Public_Card.DT_LevelUpCard_Public_Card"));
	if (PublicCardDatatable.Succeeded())
		CardDTArray.Add(PublicCardDatatable.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> KallariCardDatatable(TEXT("/Game/Data/Table/DT_LevelUpCard_Kallari.DT_LevelUpCard_Kallari"));
	if (KallariCardDatatable.Succeeded())
		CardDTArray.Add(KallariCardDatatable.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> GrimCardDatatable(TEXT("/Game/Data/Table/DT_LevelUpCard_Grim.DT_LevelUpCard_Grim"));
	if (GrimCardDatatable.Succeeded())
		CardDTArray.Add(GrimCardDatatable.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> NarbashCardDatatable(TEXT("/Game/Data/Table/DT_LevelUpCard_Narbash.DT_LevelUpCard_Narbash"));
	if (NarbashCardDatatable.Succeeded())
		CardDTArray.Add(NarbashCardDatatable.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> TerraCardDatatable(TEXT("/Game/Data/Table/DT_LevelUpCard_Terra.DT_LevelUpCard_Terra"));
	if (TerraCardDatatable.Succeeded())
		CardDTArray.Add(TerraCardDatatable.Object);
}

CLevelUpCardData::~CLevelUpCardData()
{
}

void CLevelUpCardData::ImplementCard(int8 index)
{
	check(index < FunctionsArray.Num());
	(this->*(FunctionsArray[index].Implement))();
}

const CLevelUpCardData::FCardData& CLevelUpCardData::GetCardData(int8 index) 
{
	check(index < FunctionsArray.Num());
	return FunctionsArray[index];
}


void CLevelUpCardData::InitializeCardData(ECharacterType CharacterType)
{
	check(CardDTArray[0] != nullptr);
	check(CardDTArray[int(CharacterType) + 1] != nullptr);
	

	CardImplementFuction AllPublicCardFunctions[] = {
		&CLevelUpCardData::PublicCardImplement_00,&CLevelUpCardData::PublicCardImplement_01,&CLevelUpCardData::PublicCardImplement_02,&CLevelUpCardData::PublicCardImplement_03,&CLevelUpCardData::PublicCardImplement_04,
		&CLevelUpCardData::PublicCardImplement_05,&CLevelUpCardData::PublicCardImplement_06,&CLevelUpCardData::PublicCardImplement_07,&CLevelUpCardData::PublicCardImplement_08,&CLevelUpCardData::PublicCardImplement_09,
		&CLevelUpCardData::PublicCardImplement_10,&CLevelUpCardData::PublicCardImplement_11,&CLevelUpCardData::PublicCardImplement_12,&CLevelUpCardData::PublicCardImplement_13,&CLevelUpCardData::PublicCardImplement_14,
		&CLevelUpCardData::PublicCardImplement_15,&CLevelUpCardData::PublicCardImplement_16,&CLevelUpCardData::PublicCardImplement_17,&CLevelUpCardData::PublicCardImplement_18,&CLevelUpCardData::PublicCardImplement_19,
	};
	CardImplementFuction AllCharaterCardFunctions[] = {
		&CLevelUpCardData::CharaterCardImplement_00,&CLevelUpCardData::CharaterCardImplement_01,&CLevelUpCardData::CharaterCardImplement_02,&CLevelUpCardData::CharaterCardImplement_03,&CLevelUpCardData::CharaterCardImplement_04,
		&CLevelUpCardData::CharaterCardImplement_05,&CLevelUpCardData::CharaterCardImplement_06,&CLevelUpCardData::CharaterCardImplement_07,&CLevelUpCardData::CharaterCardImplement_08,&CLevelUpCardData::CharaterCardImplement_09,
		&CLevelUpCardData::CharaterCardImplement_10,&CLevelUpCardData::CharaterCardImplement_11,&CLevelUpCardData::CharaterCardImplement_12,&CLevelUpCardData::CharaterCardImplement_13,&CLevelUpCardData::CharaterCardImplement_14,
		&CLevelUpCardData::CharaterCardImplement_15,&CLevelUpCardData::CharaterCardImplement_16,&CLevelUpCardData::CharaterCardImplement_17,&CLevelUpCardData::CharaterCardImplement_18,&CLevelUpCardData::CharaterCardImplement_19,
	};

	TArray<FName> RowNames = CardDTArray[0]->GetRowNames();
	int Index = 0;

	FCardData CardData;
	for (auto RowName : RowNames)
	{
		FLevelUpCard_Public_Card* DataTableRow = CardDTArray[0]->FindRow<FLevelUpCard_Public_Card>(FName(RowName), FString(""));

		CardData.CardName = *DataTableRow->CardName;
		CardData.SkillCardDesc = *DataTableRow->SkillCardDesc;
		CardData.Implement = AllPublicCardFunctions[Index++];

		FunctionsArray.Add(CardData);
	}
	RowNames.Empty();
	RowNames = CardDTArray[int(CharacterType) + 1]->GetRowNames();
	TotalPublicCardNum = Index;
	Index = 0;
	for (auto RowName : RowNames)
	{

		switch (CharacterType)
		{
		case ECharacterType::Kallari:
		{
			FLevelUpCard_Kallari* DataTableRow = CardDTArray[int(CharacterType) + 1]->FindRow<FLevelUpCard_Kallari>(FName(RowName), FString(""));
			CardData.CardName = *DataTableRow->CardName;
			CardData.SkillCardDesc = *DataTableRow->SkillCardDesc;
			CardData.Implement = AllCharaterCardFunctions[Index++];
			FunctionsArray.Add(CardData);
		}
			break;

		case ECharacterType::Grim:
		{
			FLevelUpCard_Grim* DataTableRow = CardDTArray[int(CharacterType) + 1]->FindRow<FLevelUpCard_Grim>(FName(RowName), FString(""));

			CardData.CardName = *DataTableRow->CardName;
			CardData.SkillCardDesc = *DataTableRow->SkillCardDesc;
			CardData.Implement = AllCharaterCardFunctions[Index++];
			FunctionsArray.Add(CardData);
		}
			break;
		case ECharacterType::Narbash:
		{
			FLevelUpCard_Narbash* DataTableRow = CardDTArray[int(CharacterType) + 1]->FindRow<FLevelUpCard_Narbash>(FName(RowName), FString(""));

			CardData.CardName = *DataTableRow->CardName;
			CardData.SkillCardDesc = *DataTableRow->SkillCardDesc;
			CardData.Implement = AllCharaterCardFunctions[Index++];
			FunctionsArray.Add(CardData);
		}
			break;
		case ECharacterType::Terra:
		{
			FLevelUpCard_Terra* DataTableRow = CardDTArray[int(CharacterType) + 1]->FindRow<FLevelUpCard_Terra>(FName(RowName), FString(""));

			CardData.CardName = *DataTableRow->CardName;
			CardData.SkillCardDesc = *DataTableRow->SkillCardDesc;
			CardData.Implement = AllCharaterCardFunctions[Index++];
			FunctionsArray.Add(CardData);

		}
		break;
		}
	}
	TotalCharacterCardNum = Index;

}
