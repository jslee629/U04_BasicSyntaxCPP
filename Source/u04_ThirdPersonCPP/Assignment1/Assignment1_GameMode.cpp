#include "Assignment1_GameMode.h"
#include "Blueprint/UserWidget.h"

AAssignment1_GameMode::AAssignment1_GameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PawnAsset(TEXT("Class'/Script/u04_ThirdPersonCPP.WPlayer'"));
	if (PawnAsset.Succeeded())
	{
		DefaultPawnClass = PawnAsset.Class;
	}

	// Load Widget class
	ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/Assignment1/UI/WB_Keys"));
	if (WidgetAsset.Succeeded())
	{
		WidgetClassToSpawn = WidgetAsset.Class;
	}
}

void AAssignment1_GameMode::StartPlay()
{
	Super::StartPlay();

	if (WidgetClassToSpawn)
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClassToSpawn);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
