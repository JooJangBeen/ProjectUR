
# pragma once

#include "Engine/DataTable.h"
#include "FGameDataTest_Sheet2.generated.h"

USTRUCT(Blueprintable)
struct FGameDataTest_Sheet2 : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

};
