// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Widgets/MainMenuWidgetBase.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidgetBase::SetPreLoginElementsVisible(bool State)
{
	
	Login->SetVisibility(State ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMainMenuWidgetBase::SetPostLoginElementsVisible(bool State)
{
	Host->SetVisibility(State ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Join->SetVisibility(State ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMainMenuWidgetBase::OnLoginClicked()
{
	bool bIsLogedIn = LoginClicked.IsBound() ? LoginClicked.Execute() : false;
	SetPostLoginElementsVisible(bIsLogedIn);
	SetPreLoginElementsVisible(!bIsLogedIn);
}

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
	Login->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnLoginClicked);
	Quit->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnQuitClicked);
	Host->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnHostClicked);
	Join->OnClicked.AddDynamic(this, &UMainMenuWidgetBase::OnJoinClicked);
}

void UMainMenuWidgetBase::NativeConstruct()
{
	SetPostLoginElementsVisible(false);
	SetPreLoginElementsVisible(true);
}