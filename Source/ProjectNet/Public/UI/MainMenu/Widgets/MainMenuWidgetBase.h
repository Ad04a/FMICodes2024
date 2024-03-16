// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Headers/UIDelegates.h"

#include "MainMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FLoginCompleteSignature);

class UButton;

UCLASS()
class PROJECTNET_API UMainMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:

	UFUNCTION()
	void OnLoginClicked();

	UFUNCTION()
	void OnJoinClicked();

	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnQuitClicked();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Login;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Host;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Join;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Quit;


	void NativeOnInitialized() override;
	void NativeConstruct() override;
	void SetPreLoginElementsVisible(bool State);
	void SetPostLoginElementsVisible(bool State);

public:
	FLoginCompleteSignature LoginClicked;
	FButtonClicked HostClicked;
	FButtonClicked JoinClicked;
	FButtonClicked QuitClicked;
	
};
