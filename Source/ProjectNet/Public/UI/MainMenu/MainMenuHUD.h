// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuWidgetBase;
class UHostSessionWidgetBase;
class UJoinSessionWidgetBase;

UCLASS()
class PROJECTNET_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidgetBase> MainMenuWidgetClass;

	UPROPERTY()
	UMainMenuWidgetBase* MainMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJoinSessionWidgetBase> JoinSessionWidgetClass;

	UPROPERTY()
	UJoinSessionWidgetBase* JoinSessionWidget;

	void Clear();

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere)
	FName HostingLevel = "Hosting";

public:

	UFUNCTION()
	void BeginHost();

	UFUNCTION()
	void ShowMenu();

	UFUNCTION()
	void ShowJoinSession();
};
