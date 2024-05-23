// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubsystem.h"
#include <Spirit/UI/UILayout.h>


UUISubsystem::UUISubsystem()
{
	static ConstructorHelpers::FClassFinder<UUILayout> BP_UILayout(TEXT("/Game/UI/BP_UILayout"));
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

		Layout = CreateWidget<UUILayout>(Controller, LayoutClass);
		if (Layout)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding UI To Viewport!"));
			// Only add to viewport if it's not already there
			if (!Layout->IsInViewport()) { 
				Layout->AddToViewport(); 
				OnUIReady.Broadcast();
			}
			
		}
	}
	else {
		//	No layout is set, what do we do?
		UE_LOG(LogTemp, Warning, TEXT("No UI Layout"))
	}
}



void UUISubsystem::PushToLayer(FUITag Tag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	OnUIReady.AddDynamic(this, &UUISubsystem::HandlePushToLayer);

	PendingTag = Tag;
	PendingWidgetClass = WidgetClass;

	//	UCommonActivatableWidgetStack* Stack = Cast<UUILayout>(Layout)->GetStack(Tag);
	//	if (Stack)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Widget added to layer"))
	//		Stack->AddWidget(WidgetClass);
	//	}
	//	else {
	//		UE_LOG(LogTemp, Warning, TEXT("Widget not found"))
	//	}
}


void UUISubsystem::HandlePushToLayer()
{
	if (Layout)
	{
		UCommonActivatableWidgetStack* Stack = Cast<UUILayout>(Layout)->GetStack(PendingTag);
		if (Stack)
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget added to layer"));
			Stack->AddWidget(PendingWidgetClass);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget not found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UILayout is null."));
	}
}