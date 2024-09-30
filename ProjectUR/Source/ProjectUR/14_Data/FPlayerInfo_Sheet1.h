
# pragma once

#include "Engine/DataTable.h"
#include "FPlayerInfo_Sheet1.generated.h"

USTRUCT(Blueprintable)
struct FPlayerInfo_Sheet1 : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damge;

};
