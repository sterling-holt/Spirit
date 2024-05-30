// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFramework.h"
#include <Components/CanvasPanel.h>
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include <Components/DynamicEntryBoxBase.h>


UUIFramework::UUIFramework()
{

}



void UUIFramework::NativeConstruct()
{
    Super::NativeConstruct();


    UE_LOG(LogTemp, Warning, TEXT("UIFramework Native Construct firing"))
}





void UUIFramework::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    UE_LOG(LogTemp, Log, TEXT("UI Framework initialized."));
}


void UUIFramework::RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack)
{

    if (Layers.Contains(Tag))
    {
        UE_LOG(LogTemp, Warning, TEXT("Layer already registered: %s"), *Tag.ToString());
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Registering Layer: %s"), *Tag.ToString());
    Layers.Add(Tag, Stack);
}


UCommonActivatableWidgetStack* UUIFramework::GetStack(FUITag Tag) const
{
    // Find the stack pointer as a const pointer
    const UCommonActivatableWidgetStack* const* StackPtr = Layers.Find(Tag);

    // Cast away the constness before returning
    return (StackPtr != nullptr) ? const_cast<UCommonActivatableWidgetStack*>(*StackPtr) : nullptr;
}