// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritPlayerState.h"

ASpiritPlayerState::ASpiritPlayerState()
{

}

void ASpiritPlayerState::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Beginning Play"))
	OnUIReady.Broadcast();
}