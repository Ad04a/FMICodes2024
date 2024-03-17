// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/HostinHUD.h"

#include "UI/MainMenu/Widgets/HostSessionWidgetBase.h"
#include "Gamemodes/Instances/PNGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/GameModeBase.h"

void AHostinHUD::BeginPlay()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AHostinHUD::BeginPlay() IsValid(World) == false"));
		return;
	}

	HostSessionWidget = CreateWidget<UHostSessionWidgetBase>(UGameplayStatics::GetGameInstance(World), HostSessionWidgetClass);
	if (IsValid(HostSessionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginPlay() IsValid(HostSessionWidget) == false"));
		return;
	}

	AGameModeBase* GameMode = Cast<AGameModeBase>(UGameplayStatics::GetGameMode(World));
	if (GameMode == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AHostinHUD::BeginPlay() IsValid(GameMode) == false"));
		return;
	}

	UPNGameInstance* GameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstance) == false) {
		UE_LOG(LogTemp, Error, TEXT("AHostinHUD::BeginPlay() IsValid(GameInstance) == false"));
		return;
	}

	if (GameInstance->HostingMode != "Host")
	{
		HostSessionWidget->SetVisibilityOfStart(false);
	}

	HostSessionWidget->OnStartClicked.AddDynamic(GameInstance, &UPNGameInstance::StartGame);
	HostSessionWidget->OnCreateClicked.BindDynamic(GameInstance, &UPNGameInstance::CreateLobby);
	HostSessionWidget->OnBackClicked.AddDynamic(this, &AHostinHUD::BackToLobby);

	ShowHostSession();
}

void AHostinHUD::BackToLobby()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AHostinHUD::BackToLobby() IsValid(World) == false"));
		return;
	}

	UPNGameInstance* GameInstance = Cast<UPNGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstance) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMainMenuHUD::BeginHost() IsValid(GameInstance) == false"));
		return;
	}
	GameInstance->HostingMode = "";
	UGameplayStatics::OpenLevel(World, FallBackLevel);

}

void AHostinHUD::ShowHostSession()
{
	if ((IsValid(PlayerOwner) && IsValid(HostSessionWidget)) == false) {
		return;
	}

	HostSessionWidget->AddToViewport();

}