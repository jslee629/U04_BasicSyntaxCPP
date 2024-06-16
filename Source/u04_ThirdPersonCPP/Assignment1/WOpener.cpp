#include "WOpener.h"
#include "Global.h"
#include "WPlayer.h"
#include "WChest.h"

void AWOpener::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (Cast<AWPlayer>(OtherActor))
	{
		if (Chest)
		{
			DrawDebugString(GetWorld(), Chest->GetActorLocation() + FVector(0, -30.f, 80.f), "Press F to open", nullptr, FColor::White, 3.f);
			Chest->CanOpen = true;
		}
	}
}

void AWOpener::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (Cast<AWPlayer>(OtherActor))
	{
		if (Chest)
		{
			Chest->CanOpen = true;
		}
	}
}
