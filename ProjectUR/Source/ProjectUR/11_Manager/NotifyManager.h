// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NotifyManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnExmNotify, int)
/*
DECLARE_MULTICAST_DELEGATE(FOnNoParam)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOneArg, AActor*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOneArg, int)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOneArg, FVector)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOneArg, void*)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTwoArgs, UPrimitiveComponent* ,AActor* )
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnThrArgs, UPrimitiveComponent*, AActor*, FVector)
DECLARE_MULTICAST_DELEGATE_NineParams()
*/

/**
 * 
 */
UCLASS()
class PROJECTUR_API UNotifyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()



#pragma region NotifyExample

public:
	FOnExmNotify OnExample;
	TMultiMap<FString, FDelegateHandle> multimapExample;

	inline void AddHandleExample(FDelegateHandle handle, FString FunctionName)
	{
		multimapExample.Add(FunctionName, handle);
	}

	inline void RemoveExample(FString FunctionName)
	{
		TArray<FDelegateHandle> Values;
		multimapExample.MultiFind(FunctionName, Values);
		if (Values.Num() > 0)
		{
			multimapExample.Remove(FunctionName, Values[0]);
			OnExample.Remove(Values[0]);
		}
	}
	inline void RemoveAllExample()
	{
		for(auto handle : multimapExample)
			OnExample.Remove(handle.Value);
		multimapExample.Empty();
	}
	inline void NotifyExample(int var)
	{
		if (OnExample.IsBound())
			OnExample.Broadcast(var);

	}

#pragma endregion



};


