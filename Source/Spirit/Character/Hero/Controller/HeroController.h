// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "HeroController.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerReady);



UCLASS()
class SPIRIT_API AHeroController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;




	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;
	UEnhancedInputComponent* EnhancedInputComponent;

public:
	AHeroController();

	void SwitchInputContext(UInputMappingContext* NewContext, int32 Priority);

	UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent; };



	//	----------------

	/* */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputMappingContext* UIContext;

	/* */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ContinueAction;

	/* */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BackAction;








	UPROPERTY(BlueprintAssignable)
	FOnControllerReady OnControllerReady;

	void HandlePawnPossessed();
	void HandlePawnUnPossessed();
};
