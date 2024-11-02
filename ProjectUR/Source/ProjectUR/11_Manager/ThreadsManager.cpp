// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadsManager.h"

UThreadsManager::~UThreadsManager()
{
    for (FThreadPoolWorker* Worker : Workers)
        Worker->Stop();

    for (FRunnableThread* Thread : WorkerThreads)
    {
        Thread->WaitForCompletion();
        delete Thread;
    }
    for (FThreadPoolWorker* Worker : Workers)
        delete Worker;


    if (ThreadEvent)
    {
        FPlatformProcess::ReturnSynchEventToPool(ThreadEvent);
        ThreadEvent = nullptr;
    }
}

void UThreadsManager::Initialize(FSubsystemCollectionBase& collection)
{
    if (ThreadEvent) 
        return;

	ThreadEvent = FPlatformProcess::GetSynchEventFromPool(true);
    IncreaseTimer = 0;
    ThreadCount = 0;

	for (ThreadCount = 0; ThreadCount <= MAXTHREADNUM; ThreadCount++)
	{
		FThreadPoolWorker* Worker = new FThreadPoolWorker(ThreadEvent, TaskQueue, QueueMutex);
		FRunnableThread* Thread = FRunnableThread::Create(Worker, *FString::Printf(TEXT("WorkerThread%d"), ThreadCount));
		WorkerThreads.Add(Thread);
		Workers.Add(Worker);
        
	}




    AddTask([&](){
        if (!TaskQueue.IsEmpty())
        {
            IncreaseTimer += THRAEADTIMER;

            if (IncreaseTimer > 1)
            {
                FThreadPoolWorker* Worker = new FThreadPoolWorker(ThreadEvent, TaskQueue, QueueMutex);
                FRunnableThread* Thread = FRunnableThread::Create(Worker, *FString::Printf(TEXT("WorkerThread%d"), ThreadCount++));
                WorkerThreads.Add(Thread);
                Workers.Add(Worker);
                IncreaseTimer = 0;

            }


            ThreadEvent->Trigger();
        }
        else
        {
            IncreaseTimer = 0;
        }

        return THRAEADTIMER;
        });

}

void UThreadsManager::AddTask(std::function<double()> Task)
{
    {
        std::lock_guard<std::mutex> Lock(QueueMutex);
        TaskQueue.Enqueue(Task);
        
    }

    ThreadEvent->Trigger();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32 FThreadPoolWorker::Run()
{
    while (!bStopTask)
    {
        Event->Wait();
        Event->Reset();



        std::function<double()> Task = nullptr;

        {
            std::lock_guard<std::mutex> Lock(QueueMutex);

            if (!TaskQueue.Dequeue(Task))
            {
                continue;
            }
        }

        if (Task != nullptr)
        {
            double val = Task();
            
            while (val != 0 && !bStopTask)
            {
                FPlatformProcess::Sleep(val);
                val = Task();
            }
            
        }
    }

    return 0;
}

void FThreadPoolWorker::Stop()
{
    bStopTask = true;
    Event->Trigger();
}
