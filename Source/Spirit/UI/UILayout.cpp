// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayout.h"
#include <Spirit/Character/Hero/Controller/HeroController.h>
#include "UObject/NoExportTypes.h"






void UUILayout::RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack)
{
	UE_LOG(LogTemp, Warning, TEXT("Registering Layer"))
	Layers.Add(Tag, Stack);
}

UCommonActivatableWidgetStack* UUILayout::GetStack(FUITag Tag) const
{
	UE_LOG(LogTemp, Warning, TEXT("Returning Stack"))
	UCommonActivatableWidgetStack* const* FoundStack = Layers.Find(Tag);
	return (FoundStack != nullptr) ? *FoundStack : nullptr;
	//	return nullptr;


	UE_LOG(LogTemp, Warning, TEXT("testing"))
}