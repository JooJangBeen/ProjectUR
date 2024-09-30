
# pragma once

#include "Engine/DataTable.h"
#include "FLevelUpCard_Public_Card.generated.h"

USTRUCT(Blueprintable)
struct FLevelUpCard_Public_Card : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillCardDesc;

};
