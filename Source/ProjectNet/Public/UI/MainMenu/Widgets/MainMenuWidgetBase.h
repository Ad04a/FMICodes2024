// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Headers/UIDelegates.h"

#include "MainMenuWidgetBase.generated.h"

class UButton;

UCLASS()
class PROJECTNET_API UMainMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:

	UFUNCTION()
	void OnJoinClicked();

	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnQuitClicked();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Host;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Join;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Quit;


	void NativeOnInitialized() override;

public:
	FButtonClicked HostClicked;
	FButtonClicked JoinClicked;
	FButtonClicked QuitClicked;
	
};
