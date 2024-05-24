// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NakamaSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SPIRIT_API UNakamaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	


private:
	FString ServerKey;
	FString Host;
	int32 Port;
	bool bUseSSL;
	bool bEnableDebug;


protected:
	void Initialize(FSubsystemCollectionBase& Collection);


public:
	UNakamaSubsystem();
};






/*


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//	#include "Engine/GameInstance.h"
#include "Delegates/Delegate.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "NakamaUnreal.h"
#include "NakamaClient.h"
#include "NakamaSession.h"
#include "NakamaRealtimeClient.h"
#include "NakamaSubsystem.generated.h"




//	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuthUpdate);




UCLASS(BlueprintType)
class STARFALL_API UNakamaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()





public:
	//	UFUNCTION(BlueprintCallable)
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	virtual void Deinitialize() override;


	// Event dispatched when authentication completes
	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	FOnError AuthenticationErrorDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	FOnAuthUpdate AuthenticationSuccessDelegate;





	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnRealtimeClientConnected RealtimeClientConnectionSuccessDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnRealtimeClientConnectionError RealtimeClientConnectionErrorDelegate;


	UFUNCTION(BlueprintCallable)
	void ConnectToRealtimeClient(UNakamaSession* Session);


	//	UFUNCTION(BlueprintCallable)
	//	void OnRealtimeClientConnectSuccess();
	//
	//	UFUNCTION(BlueprintCallable)
	//	void OnRealtimeClientConnectError(const FNakamaRtError& ErrorData);









FString PlatformAuthToken;


UFUNCTION(BlueprintCallable)
void AuthenticatePlayer();


UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
UNakamaSession* NakamaSession;
//	UNakamaSession* GetNakamaSession() const { return Session; };


UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
UNakamaClient* NakamaClient;
//	UNakamaClient* GetNakamaClient() const { return Client; };


UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
UNakamaRealtimeClient* NakamaRtClient;
//	UNakamaRealtimeClient* GetRtClient() const { return RtClient; };
};



*/