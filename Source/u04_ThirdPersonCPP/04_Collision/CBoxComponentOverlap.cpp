#include "CBoxComponentOverlap.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

ACBoxComponentOverlap::ACBoxComponentOverlap()
{
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLightComp->SetupAttachment(RootComp);
	PointLightComp->SetLightColor(FLinearColor::Green);
}

void ACBoxComponentOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLightComp->SetVisibility(true);
}

void ACBoxComponentOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLightComp->SetVisibility(false);
}

void ACBoxComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLightComp->SetVisibility(false);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACBoxComponentOverlap::ComponentBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACBoxComponentOverlap::ComponentEndOverlap);
}