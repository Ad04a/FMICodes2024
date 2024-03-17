// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Widgets/HostSessionWidgetBase.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UHostSessionWidgetBase::SetVisibilityOfStart(bool State)
{
	if (!State)
	{
		StartButton->SetVisibility(ESlateVisibility::Collapsed);
		CreateButton->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	StartButton->SetVisibility(ESlateVisibility::Visible);
	CreateButton->SetVisibility(ESlateVisibility::Visible);
}

void UHostSessionWidgetBase::NativeOnInitialized()
{
	SessionName->OnTextChanged.AddDynamic(this, &UHostSessionWidgetBase::MangeEnteredText);
	BackButton->OnClicked.AddDynamic(this, &UHostSessionWidgetBase::BackClicked);
	StartButton->OnClicked.AddDynamic(this, &UHostSessionWidgetBase::StartClicked);
	CreateButton->OnClicked.AddDynamic(this, &UHostSessionWidgetBase::CreateClicked);
}

void UHostSessionWidgetBase::NativeConstruct()
{
	SessionCode->SetText(FText::FromString(""));
	SessionName->SetText(FText::FromString(""));
}

void UHostSessionWidgetBase::MangeEnteredText(const FText& Text)
{
	if (SessionName->GetText().ToString().Len() < MaxNameLenght)
	{
		return;
	}
	FString Name = Text.ToString();
	SessionName->SetText(FText::FromString(Name.LeftChop(Name.Len() - MaxNameLenght)));
}

void UHostSessionWidgetBase::StartClicked()
{
	OnStartClicked.Broadcast();
}


void UHostSessionWidgetBase::BackClicked()
{
	OnBackClicked.Broadcast();
}

void UHostSessionWidgetBase::CreateClicked()
{
	if (OnCreateClicked.IsBound() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UHostSessionWidgetBase::CreateClicked OnCreateClicked.IsBound() == false"));
		return;
	}
	FString Code = OnCreateClicked.Execute(FName(SessionName->GetText().ToString()));
	SessionCode->SetText(FText::FromString(Code));
}
