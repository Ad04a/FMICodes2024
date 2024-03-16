// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UIDelegates.h"
#include "JoinSessionWidgetBase.generated.h"

class UEditableTextBox;
class UButton;
class UTextBlock;

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FJoinSessionSignature, FName, Key, FString, Value);

UCLASS()
class PROJECTNET_API UJoinSessionWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* SessionName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* SessionCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ErrorText;

	UPROPERTY(EditAnywhere)
	int MaxCodeLenght;

	UFUNCTION()
	void MangeEnteredText(const FText& Text);

	UFUNCTION()
	void BackClicked();

	UFUNCTION()
	void JoinClicked();

public:
	void NativeOnInitialized() override;
	void NativeConstruct() override;

	FJoinSessionSignature OnJoinClicked;
	FButtonClicked OnBackClicked;
};
