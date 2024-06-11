#include "CSpotLights.h"
#include "Global.h"
#include "Components/SpotLightComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxMultiCast.h"

ACSpotLights::ACSpotLights()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("MeshComp");
		Str.Append(FString::FromInt(i+1));
		SpotLightComps[i] = CreateDefaultSubobject<USpotLightComponent>(FName(Str));
		SpotLightComps[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLightComps[i]->SetRelativeRotation(FRotator(-90, 0, 0));

		SpotLightComps[i]->SetupAttachment(RootComp);
		SpotLightComps[i]->Intensity = 1e+5f;
		SpotLightComps[i]->OuterConeAngle = 25.f;
	}


}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxMultiCast::StaticClass(), Actors);

	if (Actors.Num() < 1) return;

	ACBoxMultiCast* Trigger = Cast<ACBoxMultiCast>(Actors[0]);
	if (Trigger)
	{
		Trigger->OnMultiCastBeginOverlap.AddUObject(this, &ACSpotLights::OnLight);
	}
}

void ACSpotLights::OnLight(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLightComps[i]->SetLightColor(FLinearColor::White);
	}

	SpotLightComps[InIndex]->SetLightColor(InColor);
}


