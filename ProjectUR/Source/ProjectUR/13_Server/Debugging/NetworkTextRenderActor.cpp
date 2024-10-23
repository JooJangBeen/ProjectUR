// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkTextRenderActor.h"

FString ANetworkTextRenderActor::GetNetMode()
{
	ENetMode NetMode = GetWorld()->GetNetMode();

	switch (NetMode)
	{
	case ENetMode::NM_Standalone: return TEXT("Standalone");
	case ENetMode::NM_ListenServer: return TEXT("ListenServer");
	case ENetMode::NM_DedicatedServer: return TEXT("DedicatedServer");
	case ENetMode::NM_Client: return TEXT("Client");
	}
	return TEXT("반가워요~");
}
