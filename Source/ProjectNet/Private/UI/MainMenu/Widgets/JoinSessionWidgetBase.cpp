// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Widgets/JoinSessionWidgetBase.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UJoinSessionWidgetBase::NativeOnInitialized()
{
	SessionCode->OnTextChanged.AddDynamic(this, &UJoinSessionWidgetBase::MangeEnteredText);
	BackButton->OnClicked.AddDynamic(this, &UJoinSessionWidgetBase::BackClicked);
	JoinButton->OnClicked.AddDynamic(this, &UJoinSessionWidgetBase::JoinClicked);
}

void UJoinSessionWidgetBase::NativeConstruct()
{
	SessionCode->SetText(FText::FromString(""));
	SessionName->SetText(FText::FromString(""));
	ErrorText->SetText(FText::FromString(""));
}

void UJoinSessionWidgetBase::MangeEnteredText(const FText& Text)
{
	if (SessionCode->GetText().ToString().Len() < MaxCodeLenght)
	{
		return;
	}
	FString Name = Text.ToString();
	SessionCode->SetText(FText::FromString(Name.LeftChop(Name.Len() - MaxCodeLenght)));
}

void UJoinSessionWidgetBase::JoinClicked()
{
	if (OnJoinClicked.IsBound() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UJoinSessionWidgetBase::JoinClicked OnJoinClicked.IsBound() == false"));
		return;
	}
	OnJoinClicked.Execute(FName(SessionName->GetText().ToString()), SessionCode->GetText().ToString());
}


void UJoinSessionWidgetBase::BackClicked()
{
	OnBackClicked.Broadcast();
}