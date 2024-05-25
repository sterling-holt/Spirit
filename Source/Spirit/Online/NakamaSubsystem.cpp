// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaSubsystem.h"
//	#include <NakamaRealtimeClient.h>

UNakamaSubsystem::UNakamaSubsystem()
{
	//	Default Client Parameters
	ServerKey = TEXT("defaultkey");
	Host = TEXT("127.0.0.1");
	Port = 7350;
	bUseSSL = false;
	bEnableDebug = true;
}

void UNakamaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Error, TEXT("NAKAMA SUBSYSTEM GO VROOM"));

	NakamaClient = UNakamaClient::CreateDefaultClient(ServerKey, Host, Port, bUseSSL, bEnableDebug);
	this->AuthenticatePlayer();
}

void UNakamaSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Display, TEXT("De-initializing NAKAMA SUBSYSTEM"));
}


void UNakamaSubsystem::AuthenticatePlayer()
{

	UE_LOG(LogTemp, Warning, TEXT("Nakama Authenticating player"))


	//	Authentication Parameters
	//	FString Email = TEXT("debug@mail.com");
	//	FString Password = TEXT("verysecretpassword");
	//	FString Username = TEXT("exo");
	//	TMap<FString, FString> Variables;


	PlatformAuthToken = "test";
		
	if (!PlatformAuthToken.IsEmpty())
	{
		//	Typically you would get the system's unique device identifier here.
		FString DeviceId = TEXT("<DeviceId>");
		FString Username = TEXT("<Username>");
		bool bCreate = true;
		TMap<FString, FString> Vars;

		AuthenticationSuccessDelegate.AddDynamic(this, &UNakamaSubsystem::HandleAuthSuccess);

		
		AuthenticationErrorDelegate.AddDynamic(this, &UNakamaSubsystem::HandleAuthError);

		NakamaClient->AuthenticateDevice(DeviceId, Username, bCreate, Vars, AuthenticationSuccessDelegate, AuthenticationErrorDelegate);
	}
	else {
		//	Get Platform Auth Token
		UE_LOG(LogTemp, Display, TEXT("Platform auth token is empty"));
	}
}




void UNakamaSubsystem::HandleAuthSuccess(UNakamaSession* Session)
{
	UE_LOG(LogTemp, Warning, TEXT("Nakama Auth Success"))
	//	this->ConnectToRealtimeClient(Session);
}
void UNakamaSubsystem::HandleAuthError(const FNakamaError& Error)
{

}

void UNakamaSubsystem::ConnectToRealtimeClient(UNakamaSession* Session)
{
	UE_LOG(LogTemp, Display, TEXT("Player is authenticated"));

	//	Update our session to the passed thru input
	NakamaSession = Session;

	NakamaRtClient = NakamaClient->SetupRealtimeClient();

	bool bCreateStatus = true;
	NakamaRtClient->Connect(NakamaSession, bCreateStatus, RealtimeClientConnectionSuccessDelegate, RealtimeClientConnectionErrorDelegate);

	//	RealtimeClientConnectionSuccessDelegate.AddDynamic(this, &UNakamaSubsystem::HandleAuthSuccess);
	//	RealtimeClientConnectionErrorDelegate.AddDynamic(this, &UNakamaSubsystem::HandleAuthSuccess);
}