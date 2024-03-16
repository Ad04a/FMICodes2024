// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/Instances/PNGameInstance.h"

#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"

bool UPNGameInstance::Login()
{

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); 

	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

	if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		return true;
	}

	LoginDelegateHandle =
		Identity->AddOnLoginCompleteDelegate_Handle(
			0,
			FOnLoginCompleteDelegate::CreateUObject(
				this,
				&ThisClass::HandleLoginCompleted));

	FString AuthType;
	FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);

	bool LoginSuccess = false;

	if (AuthType.IsEmpty()) 
	{
		FOnlineAccountCredentials Credentials("AccountPortal", "", "");
		LoginSuccess = Identity->Login(0, Credentials);
	}
	else
	{
		LoginSuccess = Identity->AutoLogin(0);
	}

	
	UE_LOG(LogTemp, Log, TEXT("Logging into EOS..."));

	if (!LoginSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); 
		Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
		LoginDelegateHandle.Reset();
	}
	return LoginSuccess;
}


void UPNGameInstance::HandleLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Login callback completed!"));;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("EOS login failed."));
	}

	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
	LoginDelegateHandle.Reset();
}

void UPNGameInstance::CreateLobby(FName KeyName, FString KeyValue)
{

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	CreateLobbyDelegateHandle =
		Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleCreateLobbyCompleted));

	TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
	SessionSettings->NumPublicConnections = 2; 
	SessionSettings->bShouldAdvertise = true; 
	SessionSettings->bUsesPresence = false;   
	SessionSettings->bAllowJoinViaPresence = false;
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
	SessionSettings->bAllowInvites = false;    
	SessionSettings->bAllowJoinInProgress = false; 
	SessionSettings->bIsDedicated = false; 
	SessionSettings->bUseLobbiesIfAvailable = true; 
	SessionSettings->bUseLobbiesVoiceChatIfAvailable = true; 
	SessionSettings->bUsesStats = true; 
	SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

	UE_LOG(LogTemp, Log, TEXT("Creating Lobby..."));

	if (!Session->CreateSession(0, LobbyName, *SessionSettings))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create Lobby!"));
	}
}

void UPNGameInstance::HandleCreateLobbyCompleted(FName EOSLobbyName, bool bWasSuccessful)
{

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UPNGameInstance::HandleCreateLobbyCompleted IsValid(World) == false"));
	}

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Lobby: %s Created!"), *EOSLobbyName.ToString());
		FURL TravelURL;
		TravelURL.Map = Map;
		World->Listen(TravelURL);
		SetupNotifications();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create lobby!"));
	}

	Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateLobbyDelegateHandle);
	CreateLobbyDelegateHandle.Reset();
}

void UPNGameInstance::SetupNotifications()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	Session->AddOnSessionParticipantsChangeDelegate_Handle(FOnSessionParticipantsChangeDelegate::CreateUObject(
		this,
		&ThisClass::HandleParticipantChanged));
}

void UPNGameInstance::HandleParticipantChanged(FName EOSLobbyName, const FUniqueNetId& NetId, bool bJoined)
{
	if (bJoined)
	{
		UE_LOG(LogTemp, Log, TEXT("A player has joined Lobby: %s"), *LobbyName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("A player has left Lobby: %s"), *LobbyName.ToString());
	}
}

void UPNGameInstance::FindLobbies(FName SearchKey, FString SearchValue)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

	Search->QuerySettings.SearchParams.Empty();

	Search->QuerySettings.Set(SearchKey, SearchValue, EOnlineComparisonOp::Equals);
	Search->QuerySettings.Set("LOBBYSEARCH", true, EOnlineComparisonOp::Equals);

	FindLobbiesDelegateHandle =
		Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleFindLobbiesCompleted,
			Search));

	UE_LOG(LogTemp, Log, TEXT("Finding lobby."));


	if (!Session->FindSessions(0, Search))
	{
		UE_LOG(LogTemp, Log, TEXT("Finding lobby failed."));
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindLobbiesDelegateHandle);
		FindLobbiesDelegateHandle.Reset();
	}
}

void UPNGameInstance::HandleFindLobbiesCompleted(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Find lobby failed."));
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindLobbiesDelegateHandle);
		FindLobbiesDelegateHandle.Reset();
		return;
	}
	// added code here to not run into issues when searching for sessions is succesfull, but the number of sessions is 0
	if (Search->SearchResults.Num() == 0)
	{
		CreateLobby();
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Found lobby."));


	for (auto SessionInSearchResult : Search->SearchResults)
	{
		
		if (SessionInSearchResult.IsValid() == false)
		{
			continue;
		}

		//Ensure the connection string is resolvable and store the info in ConnectString and in SessionToJoin
		if (Session->GetResolvedConnectString(SessionInSearchResult, NAME_GamePort, ConnectString))
		{
			LobbyToJoin = &SessionInSearchResult;
		}

		break;
	}
	JoinLobby();


}


void UPNGameInstance::JoinLobby()
{
	// Tutorial 4: Join the session.
	// Tutorial 7: Same code is used to join the lobby - just some tweaks to the logging 

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	JoinLobbyDelegateHandle =
		Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleJoinLobbyCompleted));

	UE_LOG(LogTemp, Log, TEXT("Joining Lobby."));
	if (!Session->JoinSession(0, "SessionName", *LobbyToJoin))
	{
		UE_LOG(LogTemp, Log, TEXT("Join Lobby failed."));
		Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinLobbyDelegateHandle);
		JoinLobbyDelegateHandle.Reset();
	}
}

void UPNGameInstance::HandleJoinLobbyCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Log, TEXT("Joined lobby."));
		//ClientTravel(ConnectString, TRAVEL_Absolute);
		SetupNotifications();
	}

	Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinLobbyDelegateHandle);
	JoinLobbyDelegateHandle.Reset();
}