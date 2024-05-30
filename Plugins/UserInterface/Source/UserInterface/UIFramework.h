// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "UITag.h"
#include "CommonActivatableWidget.h"
#include <Widgets/CommonActivatableWidgetContainer.h>
#include "UIFramework.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUIFramework : public UCommonUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack);

	UCommonActivatableWidgetStack** SelectedLayer;
		


public:
	UUIFramework();


	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TMap<FUITag, UCommonActivatableWidgetStack*> Layers;
	


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Watermark;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Game;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* HUD;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Menu;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Modal;






	//	------------

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidgetStack* GetStack(FUITag Tag) const;
};