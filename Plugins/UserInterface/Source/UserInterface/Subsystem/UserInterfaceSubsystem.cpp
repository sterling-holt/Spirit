// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaceSubsystem.h"
#include "Engine/World.h"						// Include for FWorldDelegates
#include "GameFramework/PlayerState.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CommonUserWidget.h"
#include <UserInterface/Settings/UISettings.h>
#include <UserInterface/UIFramework.h>
#include <AssetRegistry/AssetRegistryModule.h>



UUserInterfaceSubsystem::UUserInterfaceSubsystem()
{
	//	We have established our settings,
	//	So we can reference those instead of relying on hardcoded BP references!
	// 
	//	----------------------------
	// 



	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByPath(FName("/UserInterface"), AssetData, true);

	for (const FAssetData& Data : AssetData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found asset: %s"), *Data.AssetName.ToString());
	}

	FString AssetPath = TEXT("/UserInterface/BP_UIFramework.BP_UIFramework_C");
	UClass* BlueprintClass = StaticLoadClass(UObject::StaticClass(), nullptr, *AssetPath);
	if (BlueprintClass)
	{
		FrameworkClass = BlueprintClass;
		UE_LOG(LogTemp, Warning, TEXT("Successfully found the MyUIFramework blueprint dynamically."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find the MyUIFramework blueprint dynamically. Path used: %s"), *AssetPath);
	}
}


void UUserInterfaceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//	UE_LOG(LogTemp, Warning, TEXT("Initializing UI Subsystem"))
	//	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UUserInterfaceSubsystem::OnPostWorldInitialization);
	OnUIReady.AddDynamic(this, &UUserInterfaceSubsystem::Test);
}


void UUserInterfaceSubsystem::Test()
{
	UE_LOG(LogTemp, Error, TEXT("FUCKING"))
}
/*
void UUserInterfaceSubsystem::OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	if (World)
	{
		World->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &UUserInterfaceSubsystem::OnPlayerControllerSpawned));
	}
}




void UUserInterfaceSubsystem::OnPlayerControllerSpawned(AActor* Actor)
{
	APlayerController* PlayerController = Cast<APlayerController>(Actor);
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller detected for UI!"));

		OnUIReady.Broadcast(PlayerController);
	}
}
*/



void UUserInterfaceSubsystem::DisplayUI(APlayerController* PlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("OnUIReady triggered!"))

	if (FrameworkClass && GetWorld()->IsGameWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("FrameworkClass found"))
		Framework = Cast<UUIFramework>(CreateWidget<UCommonUserWidget>(PlayerController, FrameworkClass));
		if (Framework)
		{
			UE_LOG(LogTemp, Warning, TEXT("Framework found"))
			Framework->SetVisibility(ESlateVisibility::Visible);
			if (!Framework->IsInViewport())
			{
				Framework->AddToViewport();
				OnUIReady.Broadcast();
				UE_LOG(LogTemp, Warning, TEXT("Layout added to viewport"));
			}
			else { UE_LOG(LogTemp, Warning, TEXT("Layout is already in viewport, skipping to next step.")) }
		}
		else { UE_LOG(LogTemp, Warning, TEXT("Layout could not be created")) }
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("FrameworkClass not found"))
	}
}




UCommonActivatableWidget* UUserInterfaceSubsystem::PushWidget(FUITag Tag, TSubclassOf<UCommonActivatableWidget> Widget)
{
	if (Framework) {
		//	UE_LOG(LogTemp, Warning, TEXT("working on widget"))
		//	UCommonActivatableWidgetStack* Stack = Framework->GetStack(Tag);
		//	UCommonActivatableWidget* Test = Stack->AddWidget(Widget);

		return nullptr;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not working on widget"))
		return nullptr;
	}

	//	syntax: BP_AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
	//	Stack->AddWidget(Widget);
}


//	void UUserInterfaceSubsystem::HandlePush()
//	{
//	
//	}





























/*
void UUserInterfaceSubsystem::OnPlayerStateReady()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerState is ready. Initializing UI."));

	// Initialize your UI here
	const UUISettings* UISettings = GetDefault<UUISettings>();
	if (UISettings)
	{
		if (UISettings->StartupWidget)
		{
			UUserWidget* StartupWidget = CreateWidget<UUserWidget>(GetWorld(), UISettings->StartupWidget);
			if (StartupWidget)
			{
				StartupWidget->AddToViewport();
			}
		}

		// Repeat for other widgets as necessary
	}
}



*
























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
}
*/