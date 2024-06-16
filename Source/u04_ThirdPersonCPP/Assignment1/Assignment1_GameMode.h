// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment1_GameMode.generated.h"

class UUserWidget;

UCLASS()
class U04_THIRDPERSONCPP_API AAssignment1_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAssignment1_GameMode();
	virtual void StartPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* Widget;
	TSubclassOf<UUserWidget> WidgetClassToSpawn;		// 위젯 스폰을 위한 클래스 레퍼런스
};
