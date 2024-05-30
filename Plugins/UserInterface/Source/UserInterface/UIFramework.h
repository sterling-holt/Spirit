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
 * UUIFramework
 *
 * A class that handles the framework for the user interface. Inherits from UCommonUserWidget.
 * This class provides functionalities for registering and managing different UI layers using gameplay tags.
 */



 // Enum to represent UI layers
UENUM(BlueprintType)
enum class EUILayerTag : uint8
{
	Watermark UMETA(DisplayName = "Watermark"),
	Game UMETA(DisplayName = "Game"),
	HUD UMETA(DisplayName = "HUD"),
	Menu UMETA(DisplayName = "Menu"),
	Modal UMETA(DisplayName = "Modal")
};



UCLASS()
class USERINTERFACE_API UUIFramework : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	/**
	 * NativeConstruct
	 *
	 * Called when the widget is constructed.
	 * Override this function to provide additional initialization.
	 */
	virtual void NativeConstruct() override;

	/**
	 * NativeOnInitialized
	 *
	 * Called once after the widget is initialized.
	 * Override this function to provide additional initialization.
	 */
	virtual void NativeOnInitialized() override;

	/**
	 * RegisterLayer
	 *
	 * Registers a UI layer with the specified tag and stack.
	 *
	 * @param Tag The gameplay tag associated with the UI layer.
	 * @param Stack The stack widget to be associated with the tag.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RegisterLayer(FUITag Tag, UCommonActivatableWidgetStack* Stack);

	// Pointer to the currently selected layer
	UCommonActivatableWidgetStack** SelectedLayer;


private:


public:
	// Constructor
	UUIFramework();

	// Mapping enum to gameplay tags

	//	UFUNCTION(BlueprintCallable)
	//	FUITag GetFUITagFromEnum(EUILayerTag EnumTag) const;


	// Map of layers associated with their respective gameplay tags
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TMap<FUITag, UCommonActivatableWidgetStack*> Layers;

	// Widget stack for the watermark layer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Watermark;

	// Widget stack for the game layer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Game;

	// Widget stack for the HUD layer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* HUD;

	// Widget stack for the menu layer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Menu;

	// Widget stack for the modal layer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonActivatableWidgetStack* Modal;

	/**
	 * GetStack
	 *
	 * Returns the widget stack associated with the specified tag.
	 *
	 * @param Tag The gameplay tag associated with the UI layer.
	 * @return The widget stack associated with the tag.
	 */
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidgetStack* GetStack(FUITag Tag) const;
};
