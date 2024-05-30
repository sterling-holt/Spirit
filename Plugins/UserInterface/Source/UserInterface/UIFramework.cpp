// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFramework.h"
#include <Components/CanvasPanel.h>
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include <Components/DynamicEntryBoxBase.h>


UUIFramework::UUIFramework()
{
    //  FGameplayTag VersionTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("VersionTag"));
    //  FGameplayTag MyTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("MyTagName"));
    //  FGameplayTag MyTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("MyTagName"));
    //  FGameplayTag MyTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("MyTagName"));
    //  FGameplayTag MyTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("MyTagName"));
}



void UUIFramework::NativeConstruct()
{
    Super::NativeConstruct();

    if (!WidgetTree)
    {
        UE_LOG(LogTemp, Error, TEXT("WidgetTree is null!"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("WidgetTree is initialized successfully."));
    }

    // Create a Canvas Panel as the root widget
    UCanvasPanel* RootPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootPanel"));
    if (!RootPanel)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create RootPanel!"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("RootPanel created successfully."));
    }








    WidgetTree->RootWidget = RootPanel;




    //  UOverlayPanelWidget* Overlay = WidgetTree->ConstructWidget<UOverlayPanelWidget>(UOverlayPanelWidget::StaticClass(), TEXT(""));

    //  ----
    // 
    // 
    // 
    // 
    //  Create a TextBlock
    //  MyTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("MyTextBlock"));
    //  if (MyTextBlock)
    //  {
    //      MyTextBlock->SetText(FText::FromString(TEXT("Hello, World!")));
    //      UE_LOG(LogTemp, Log, TEXT("MyTextBlock created successfully."));
    //  
    //      // Add the TextBlock to the Canvas Panel
    //      UCanvasPanelSlot* CanvasSlot = RootPanel->AddChildToCanvas(MyTextBlock);
    //      if (CanvasSlot)
    //      {
    //          CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    //          CanvasSlot->SetOffsets(FMargin(0.0f, 0.0f));
    //          CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
    //          UE_LOG(LogTemp, Log, TEXT("MyTextBlock added to CanvasPanel successfully."));
    //      }
    //      else
    //      {
    //          UE_LOG(LogTemp, Error, TEXT("Failed to create CanvasSlot!"));
    //      }
    //  }
    //  else
    //  {
    //      UE_LOG(LogTemp, Error, TEXT("Failed to create MyTextBlock!"));
    //  }
}





void UUIFramework::NativeOnInitialized()
{
    UE_LOG(LogTemp, Log, TEXT("UI Framework initialized."))
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