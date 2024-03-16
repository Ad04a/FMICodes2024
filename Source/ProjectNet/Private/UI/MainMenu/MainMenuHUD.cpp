// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuHUD.h"

#include "UI/MainMenu/Widgets/HostSessionWidgetBase.h"
#include "UI/MainMenu/Widgets/JoinSessionWidgetBase.h"
#include "UI/MainMenu/Widgets/MainMenuWidgetBase.h"
#include "Gamemodes/Instances/PNGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
//#include "GameModes/MainMenuModeBase.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(World) == false"));
		return;
	}

	/*AMainMenuModeBase* GameMode = Cast<AMainMenuModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(GameMode) == false"));
		return;
	}*/

	UPNGameInstance* GameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstance) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(GameInstance) == false"));
		return;
	}

	MainMenuWidget = CreateWidget<UMainMenuWidgetBase>(UGameplayStatics::GetGameInstance(World), MainMenuWidgetClass);
	if (IsValid(MainMenuWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(MainMenuWidget) == false"));
		return;
	}

	HostSessionWidget = CreateWidget<UHostSessionWidgetBase>(UGameplayStatics::GetGameInstance(World), HostSessionWidgetClass);
	if (IsValid(HostSessionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(HostSessionWidget) == false"));
		return;
	}

	JoinSessionWidget = CreateWidget<UJoinSessionWidgetBase>(UGameplayStatics::GetGameInstance(World), JoinSessionWidgetClass);
	if (IsValid(JoinSessionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(JoinSessionWidget) == false"));
		return;
	}

	MainMenuWidget->LoginClicked.BindDynamic(GameInstance, &UPNGameInstance::Login);
	MainMenuWidget->QuitClicked.AddDynamic(this, &AMainMenuHUD::ShowMenu);
	MainMenuWidget->HostClicked.AddDynamic(this, &AMainMenuHUD::ShowHostSession);
	MainMenuWidget->JoinClicked.AddDynamic(this, &AMainMenuHUD::ShowJoinSession);

	//HostSessionWidget->OnCreateClicked.AddDynamic(GameMode, &AMainMenuModeBase::StartGame);
	//HostSessionWidget->OnStartClicked.BindDynamic(this, &AMainMenuHUD::ShowMenu);
	HostSessionWidget->OnBackClicked.AddDynamic(this, &AMainMenuHUD::ShowMenu);

    
	JoinSessionWidget->OnBackClicked.AddDynamic(this, &AMainMenuHUD::ShowMenu);
	//JoinSessionWidget->OnJoinClicked.BindDynamic(GameMode, &AMainMenuModeBase::AddSave);
	

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());

	ShowMenu();
}


void AMainMenuHUD::ShowMenu()
{
	if ((IsValid(PlayerOwner) && IsValid(MainMenuWidget)) == false) {
		return;
	}

	Clear();

	MainMenuWidget->AddToViewport();

}

void AMainMenuHUD::ShowHostSession()
{
	if ((IsValid(PlayerOwner) && IsValid(HostSessionWidget)) == false) {
		return;
	}

	Clear();

	HostSessionWidget->AddToViewport();

}

void AMainMenuHUD::ShowJoinSession()
{
	if ((IsValid(PlayerOwner) && IsValid(JoinSessionWidget)) == false) {
		return;
	}
	Clear();
	JoinSessionWidget->AddToViewport();

}


void AMainMenuHUD::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}