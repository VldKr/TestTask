// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrosshairHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ACrosshairHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* CrosshairTexture;
};
