// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include <CommonUserWidget.h>
#include <UITag.h>
#include "UObject/ConstructorHelpers.h"
//	#include <Spirit/Character/Hero/Controller/HeroController.h>
#include <Widgets/CommonActivatableWidgetContainer.h>
#include <Spirit/Character/Hero/Controller/HeroController.h>
#include "UISubsystem.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIReadyDelegate);



UCLASS()
class SPIRIT_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UUISubsystem();

	void Initialize(FSubsystemCollectionBase& Collection);

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TSubclassOf<UCommonUserWidget> LayoutClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UCommonUserWidget* Layout;

	
	UPROPERTY(BlueprintAssignable, Category = "UI Event")
	FOnUIReadyDelegate OnUIReady;


	FUITag PendingTag;
	TSubclassOf<UCommonActivatableWidget> PendingWidgetClass;


	UFUNCTION(BlueprintCallable)
	void PushToLayer(FUITag Tag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

	UFUNCTION()
	void HandlePushToLayer();
	void Display(AHeroController* Controller);
};