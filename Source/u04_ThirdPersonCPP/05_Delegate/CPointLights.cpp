#include "CPointLights.h"
#include "Components/PointLightComponent.h"
#include "Global.h"
#include "CBoxDelegate.h"

ACPointLights::ACPointLights()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	PointLightComp1 = CreateDefaultSubobject<UPointLightComponent>("PointLightComp1");
	PointLightComp1->SetupAttachment(RootComp);

	PointLightComp2 = CreateDefaultSubobject<UPointLightComponent>("PointLightComp2");
	PointLightComp2->SetupAttachment(RootComp);

	PointLightComp1->Intensity = 1e+4f;
	PointLightComp1->AttenuationRadius = 200.f;
	PointLightComp1->LightColor = FColor(255, 128, 64);

	PointLightComp2->SetRelativeLocation(FVector(0, 200, 0));
	PointLightComp2->Intensity = 1e+4f;
	PointLightComp2->AttenuationRadius = 200.f;
	PointLightComp2->LightColor = FColor(255, 128, 64);
}

void ACPointLights::BeginPlay()
{
	Super::BeginPlay();

	PointLightComp1->SetVisibility(false);
	PointLightComp2->SetVisibility(false);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxDelegate::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		ACBoxDelegate* Trigger = Cast<ACBoxDelegate>(Actors[0]);
		if (Trigger)
		{
			//3. ¹ÙÀÎµù
			Trigger->OnBoxBeginOverlap.BindUFunction(this, "OnLights");
			Trigger->OnBoxEndOverlap.BindUFunction(this, "OffLights");
			Trigger->OnBoxOneParam.BindUFunction(this, "OnRandomLight");
		}
	}
}

void ACPointLights::OnLights()
{
	PointLightComp1->SetVisibility(true);
}

void ACPointLights::OffLights()
{
	PointLightComp1->SetVisibility(false);
	PointLightComp2->SetVisibility(false);
}

FString ACPointLights::OnRandomLight(FLinearColor InColor)
{
	PointLightComp2->SetVisibility(true);
	PointLightComp2->SetLightColor(InColor);
	FString RtnStr = FString::Printf(TEXT("RandomColor is %s"), *InColor.ToString());
	return RtnStr;
}


