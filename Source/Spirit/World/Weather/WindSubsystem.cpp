// Fill out your copyright notice in the Description page of Project Settings.


#include "WindSubsystem.h"

UWindSubsystem::UWindSubsystem()
{
	UE_LOG(LogTemp, Warning, TEXT("Wind gon' blow"))
}


void UWindSubsystem::UpdateWind(FVector NewDirection, float NewSpeed)
{
    WindDirection = NewDirection;
    WindSpeed = NewSpeed;
}