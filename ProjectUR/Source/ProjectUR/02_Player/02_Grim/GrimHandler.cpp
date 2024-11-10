// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimHandler.h"

GrimHandler::GrimHandler()
{
}

GrimHandler::~GrimHandler()
{
}

void GrimHandler::ProcessNetworkPacket()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("asdasdsadasd"));
	return;
}