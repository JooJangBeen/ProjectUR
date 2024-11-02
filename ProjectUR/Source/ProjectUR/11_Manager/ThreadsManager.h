// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/PlatformProcess.h"
#include "Containers/Queue.h"
#include <functional>
#include <mutex>
#define MAXTHREADNUM 8
#define THRAEADTIMER 0.016
#include "ThreadsManager.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTUR_API UThreadsManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual ~UThreadsManager();
protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

public:
	void AddTask(std::function<double()> Task);

private:
	FEvent* ThreadEvent;
	std::mutex QueueMutex;
	TQueue<std::function<double()>> TaskQueue;
	TArray<FRunnableThread*> WorkerThreads;
	TArray<class FThreadPoolWorker*> Workers;
	double IncreaseTimer;
	int ThreadCount;
};


class FThreadPoolWorker : public FRunnable
{
public:
	FThreadPoolWorker(FEvent* InEvent, TQueue<std::function<double()>>& InTaskQueue, std::mutex& InMutex)
		: bStopTask(false), Event(InEvent), TaskQueue(InTaskQueue), QueueMutex(InMutex) {}

	virtual uint32 Run() override;
	virtual void Stop() override;


	FThreadSafeBool bStopTask;
	FEvent* Event = nullptr;
	TQueue<std::function<double()>>& TaskQueue;
	std::mutex& QueueMutex;

};