// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayout.h"
#include <Spirit/Character/Hero/Controller/HeroController.h>
#include "UObject/NoExportTypes.h"






void UUILayout::RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack)
{
    if (Layers.Contains(Tag))
    {
        UE_LOG(LogTemp, Warning, TEXT("Layer already registered: %s"), *Tag.ToString());
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Registering Layer: %s"), *Tag.ToString());
    Layers.Add(Tag, Stack);
}




UCommonActivatableWidgetStack* UUILayout::GetStack(FUITag Tag) const
{
    // Find the stack pointer as a const pointer
    const UCommonActivatableWidgetStack* const* StackPtr = Layers.Find(Tag);

    // Cast away the constness before returning
    return (StackPtr != nullptr) ? const_cast<UCommonActivatableWidgetStack*>(*StackPtr) : nullptr;
}