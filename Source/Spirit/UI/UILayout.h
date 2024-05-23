// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include <UITag.h>
#include <Widgets/CommonActivatableWidgetContainer.h>
#include <CommonActivatableWidget.h>
#include "UILayout.generated.h"

/**
 * 
 */
UCLASS()
class SPIRIT_API UUILayout : public UCommonUserWidget
{
	GENERATED_BODY()
	


protected:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack);



	UCommonActivatableWidgetStack** SelectedLayer;


	TMap<FUITag, UCommonActivatableWidgetStack*> Layers;



public:
	UCommonActivatableWidgetStack* GetStack(FUITag Tag) const;
	//	AddStack(FUITag Tag, Stack) const { return Layers.Add(Tag); };
};
