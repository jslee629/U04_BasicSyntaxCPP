#include "CBoxBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBoxBase::ACBoxBase()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootComp);
	BoxComp->bHiddenInGame = false;
	BoxComp->SetWorldScale3D(FVector(3));

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("Box");
	TextRenderComp->SetupAttachment(RootComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeRotation(FRotator(0, 0, 180));
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->TextRenderColor = FColor::Black;
	TextRenderComp->SetText(GetName());
}

void ACBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase::ActorEndOverlap);
}

void ACBoxBase::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ACBoxBase::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}


