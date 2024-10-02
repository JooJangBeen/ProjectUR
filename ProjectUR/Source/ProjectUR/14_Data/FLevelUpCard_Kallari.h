
# pragma once

#include "Engine/DataTable.h"
#include "FLevelUpCard_Kallari.generated.h"

USTRUCT(Blueprintable)
struct FLevelUpCard_Kallari : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillCardDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UseIconNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillIconChangeLevelInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString IconRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IconColor_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IconColor_G;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IconColor_B;

};
