// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UIDelegates.h"
#include "HostSessionWidgetBase.generated.h"

class UButton;
class UEditableTextBox;
class UScrollBox;
class UTextBlock;

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString, FCreateSessionSignature, FName, Key);

UCLASS()
class PROJECTNET_API UHostSessionWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* SessionName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* CreateButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SessionCode;

	UPROPERTY(EditAnywhere)
	int MaxNameLenght;

	UFUNCTION()
	void MangeEnteredText(const FText& Text);

	UFUNCTION()
	void BackClicked();

	UFUNCTION()
	void StartClicked();

	UFUNCTION()
	void CreateClicked();

public:

	void SetVisibilityOfStart(bool State);

	void NativeOnInitialized() override;
	void NativeConstruct() override;

	FCreateSessionSignature OnCreateClicked;
	FButtonClicked OnStartClicked;
	FButtonClicked OnBackClicked;

};
