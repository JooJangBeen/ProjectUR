// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
// ...가변인자를 받는것이다. 로그 매크로 선언
#define PUR_LOG(LogCat,		Verbosity, Format, ...)  UE_LOG(LogCat, Verbosity, TEXT("%s %s"), LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogNetwork, Log, All);//네트워크 로그 카테고리 지정