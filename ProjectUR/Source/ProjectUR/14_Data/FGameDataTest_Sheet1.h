
# pragma once

#include "Engine/DataTable.h"
#include "FGameDataTest_Sheet1.generated.h"

USTRUCT(Blueprintable)
struct FGameDataTest_Sheet1 : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp;

};
