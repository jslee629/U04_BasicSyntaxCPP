#include "WOpener.h"
#include "WPlayer.h"
#include "WChest.h"

void AWOpener::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
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
