
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

};
