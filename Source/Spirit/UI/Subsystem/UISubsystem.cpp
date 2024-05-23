// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubsystem.h"


UUISubsystem::UUISubsystem()
{
	static ConstructorHelpers::FClassFinder<UCommonUserWidget> BP_UILayout(TEXT("/Game/UI/BP_UILayout"));
	if (BP_UILayout.Class != NULL)
	{
		LayoutClass = BP_UILayout.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find the BP_UILayout blueprint."));
	}
}


void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Initializing UI Subsystem"))
}



void UUISubsystem::Display(AHeroController* Controller)
{
	if (LayoutClass)
	{
		//	Layout is set,
		UE_LOG(LogTemp, Warning, TEXT("Displaying UI!"))
		LayoutInstance = CreateWidget<UCommonUserWidget>(Controller, LayoutClass);
		if (LayoutInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding UI To Viewport!"));
			// Only add to viewport if it's not already there
			if (!LayoutInstance->IsInViewport()) { LayoutInstance->AddToViewport(); }
		}
	}
	else {
		//	No layout is set, what do we do?
		UE_LOG(LogTemp, Warning, TEXT("No UI Layout"))
	}
}







void UUISubsystem::PushToLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack)
{
	UE_LOG(LogTemp, Warning, TEXT("Pushing widget to layer"))
}


void UUISubsystem::CreateCommonWidget(FUITag Tag, TSubclassOf<UCommonActivatableWidgetStack*> Stack)
{
	UE_LOG(LogTemp, Warning, TEXT("Common UI Activatable STack created"))

	//	Grab Tag, search Layout.class
}