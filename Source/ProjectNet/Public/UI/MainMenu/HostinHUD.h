// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HostinHUD.generated.h"

class UHostSessionWidgetBase;

UCLASS()
class PROJECTNET_API AHostinHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHostSessionWidgetBase> HostSessionWidgetClass;

	UPROPERTY()
	UHostSessionWidgetBase* HostSessionWidget;

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere)
	FName FallBackLevel = "MainMenu";

public:

	UFUNCTION()
	void BackToLobby();

	UFUNCTION()
	void ShowHostSession();
};
