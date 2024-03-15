// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Widgets/MainMenuWidgetBase.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidgetBase::OnHostClicked()
{
	HostClicked.Broadcast();
}

void UMainMenuWidgetBase::OnJoinClicked()
{
	JoinClicked.Broadcast();
}

void UMainMenuWidgetBase::OnQuitClicked()
{
	QuitClicked.Broadcast();
}

void UMainMenuWidgetBase::NativeOnInitialized()
{
	Quit->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnQuitClicked);
	Host->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnHostClicked);
	Join->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnJoinClicked);
}