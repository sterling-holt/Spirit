// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubsystem.h"
#include "Engine/World.h"  // Include for FWorldDelegates
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CommonUserWidget.h"
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
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UUISubsystem::OnPostWorldInitialization);
}



void UUISubsystem::OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	// Defer initialization until the player controller is available
	if (World)
	{
		World->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &UUISubsystem::OnPlayerControllerSpawned));
		UE_LOG(LogTemp, Warning, TEXT("Bound to OnActorSpawned event"));
	}
}






void UUISubsystem::OnPlayerControllerSpawned(AActor* Actor)
{
	APlayerController* PlayerController = Cast<APlayerController>(Actor);
	if (PlayerController)
	{
		AHeroController* HeroController = Cast<AHeroController>(PlayerController);
		if (HeroController)
		{
			HeroController->OnControllerReady.AddDynamic(this, &UUISubsystem::DisplayUI);
			UE_LOG(LogTemp, Warning, TEXT("Bound to HeroController's OnUIReady event"));

			// Optionally remove the handler to avoid multiple bindings
			UWorld* World = GetWorld();
			if (World)
			{
				//	World->RemoveOnActorSpawnedHandler(this);
			}
		}
	}
}


void UUISubsystem::DisplayUI()
{
	UE_LOG(LogTemp, Warning, TEXT("Displaying UI!"));

	if (LayoutClass && GetWorld()->IsGameWorld())
	{
		AHeroController* Controller = Cast<AHeroController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller)
		{
			Layout = Cast<UUILayout>(CreateWidget<UCommonUserWidget>(Controller, LayoutClass));
			if (Layout)
			{
				if (!Layout->IsInViewport())
				{
					Layout->AddToViewport();
					UE_LOG(LogTemp, Warning, TEXT("Layout added to viewport"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Layout is already in viewport, skipping to next step."));
				}
				OnUIReady.Broadcast();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Layout could not be created"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No player controller found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please specify UILayout to render UI framework."));
	}
}

















void UUISubsystem::PushToLayer(FUITag Tag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{

	PendingTag = Tag;
	PendingWidgetClass = WidgetClass;


	UE_LOG(LogTemp, Warning, TEXT("I'd love to push that for you butttttt"))


	//	OnUIReady.AddDynamic(this, &UUISubsystem::HandlePushToLayer);
}


void UUISubsystem::HandlePushToLayer()
{
	UCommonActivatableWidgetStack* Stack = Layout->GetStack(PendingTag);
	if (Stack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget added to layer"))
		Stack->AddWidget(PendingWidgetClass);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Widget not found"))
	}

	/*
	if (Layout)
	{
		UE_LOG(LogTemp, Warning, TEXT("Layout found while trying to push widgets"))
	//		UCommonActivatableWidgetStack* Stack = Cast<UUILayout>(Layout)->GetStack(PendingTag);
	//		if (Stack)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Widget added to layer"));
	//	
	//			UCommonActivatableWidget* WidgetInstance = Stack->AddWidget(PendingWidgetClass);
	//			//	if (WidgetInstance)
	//			//	{
	//			//		WidgetInstance->ActivateWidget();
	//			//	}
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Widget not found"));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("UILayout is null."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No UI Layout"))
	}
	*/
}