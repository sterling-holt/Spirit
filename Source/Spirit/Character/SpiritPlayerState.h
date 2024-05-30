// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpiritPlayerState.generated.h"

/**
 * 
 */




DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIReadyDelegate);



UCLASS()
class SPIRIT_API ASpiritPlayerState : public APlayerState
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	ASpiritPlayerState();

	UPROPERTY(BlueprintAssignable)
	FOnUIReadyDelegate OnUIReady;
};
