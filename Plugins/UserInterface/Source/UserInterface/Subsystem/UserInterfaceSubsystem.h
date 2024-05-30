// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"  // Include for FWorldDelegates
#include "Engine/GameInstance.h"

#include "CommonUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "CommonActivatableWidget.h"


#include "Kismet/GameplayStatics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../UIFramework.h"
#include "UserInterfaceSubsystem.generated.h"


#pragma once



/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIReady);


UCLASS()
class USERINTERFACE_API UUserInterfaceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	UUserInterfaceSubsystem();
	//	void OnPlayerControllerSpawned(AActor* Actor);


	UPROPERTY(BlueprintAssignable)
	FOnUIReady OnUIReady;


	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUIFramework> FrameworkClass;
	
	UPROPERTY(BlueprintReadWrite, Category ="UI")
	class UUIFramework* Framework;


	UFUNCTION(BlueprintCallable)
	void DisplayUI(APlayerController* PlayerController);


	//	void OnPostLogin(APlayerController* NewPlayer);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushWidget(FUITag Tag, TSubclassOf<UCommonActivatableWidget> Widget);

private:



protected:


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//	void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
	//	void Deinitialize();
	//	void OnPlayerControllerSpawned(AActor* Actor);
	//	void InitializeUI(APlayerController* PlayerController);

	//	void OnGameStateSet(APlayerController* NewPlayer); 

	UFUNCTION()
	void Test();
};