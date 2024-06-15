#include "WPlayer.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "WChest.h"
#include "WOpener.h"

void AWPlayer::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AWPlayer::SaveOpener);
	OnActorEndOverlap.AddDynamic(this, &AWPlayer::RemoveOpener);
}

void AWPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::F, IE_Pressed, this, &AWPlayer::Open);
}

void AWPlayer::Open()
{
	if (Opener)
	{
		Opener->Chest->OpenTheChest();
	}
}

void AWPlayer::SaveOpener(AActor* OverlappedActor, AActor* OtherActor)
{
	AWOpener* NewOpener = Cast<AWOpener>(OtherActor);
	if (NewOpener)
	{
		Opener = NewOpener;
	}
}

void AWPlayer::RemoveOpener(AActor* OverlappedActor, AActor* OtherActor)
{
	AWOpener* NewOpener = Cast<AWOpener>(OtherActor);
	if (NewOpener)
	{
		Opener = nullptr;
	}
}