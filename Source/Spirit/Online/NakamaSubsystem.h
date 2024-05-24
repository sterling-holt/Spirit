// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Plugins/Nakama/Source/NakamaUnreal/Public/NakamaClient.h"
//	#include "../../../Plugins/Nakama/Source/NakamaUnreal/Public/NakamaUnreal.h"
//	#include "../../../Plugins/Nakama/Source/NakamaUnreal/Public/NakamaSession.h"
//	#include "../../../Plugins/Nakama/Source/NakamaUnreal/Public/NakamaRealtimeClient.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "NakamaSubsystem.generated.h"




//	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuthSuccess);
//	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnError);



UCLASS()
class SPIRIT_API UNakamaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	


private:
	FString PlatformAuthToken;
	FString ServerKey;
	FString Host;
	int32 Port;
	bool bUseSSL;
	bool bEnableDebug;


protected:
	void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize() override;







	//	----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
	UNakamaClient* NakamaClient;
	//	UNakamaClient* GetNakamaClient() const { return Client; };

	//	----

	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
	//	UNakamaSession* NakamaSession;
	//	UNakamaSession* GetNakamaSession() const { return Session; };

	//	----

	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama")
	//	UNakamaRealtimeClient* NakamaRtClient;
	//	UNakamaRealtimeClient* GetRtClient() const { return RtClient; };

	//	----


public:
	UNakamaSubsystem();

	void AuthenticatePlayer();

	//	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	//	FOnAuthSuccess OnAuthSuccess;
	UFUNCTION()
	void HandleAuthSuccess(UNakamaSession* Session);

	//	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	//	FOnError OnAuthError;
	UFUNCTION()
	void HandleAuthError(const FNakamaError& Error);


	//	Event dispatched when authentication completes
	//	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	//	FOnAuthSuccess OnAuthSuccess;
	//	void HandleAuthSuccess(UNakamaSession* Session);
	
	//	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	//	FOnAuthError OnAuthError;
	//	void HandleAuthError(const FNakamaError& Error);
	//	



	//	UPROPERTY(BlueprintAssignable, Category = "Character")
	//	FOnRealtimeClientConnected RealtimeClientConnectionSuccessDelegate;
	//	
	//	UPROPERTY(BlueprintAssignable, Category = "Character")
	//	FOnRealtimeClientConnectionError RealtimeClientConnectionErrorDelegate;
	//	
	//	
	//	UFUNCTION(BlueprintCallable)
	//	void ConnectToRealtimeClient(UNakamaSession* Session);


	//	UFUNCTION(BlueprintCallable)
	//	void OnRealtimeClientConnectSuccess();
	//
	//	UFUNCTION(BlueprintCallable)
	//	void OnRealtimeClientConnectError(const FNakamaRtError& ErrorData);

};