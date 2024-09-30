
# pragma once

#include "Engine/DataTable.h"
#include "FLevelUpCard_Grim.generated.h"

USTRUCT(Blueprintable)
struct FLevelUpCard_Grim : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillCardDesc;

};
