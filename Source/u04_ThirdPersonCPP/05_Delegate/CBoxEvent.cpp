#include "CBoxEvent.h"
#include "Global.h"

void ACBoxEvent::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnEventBeginOverlap.IsBound())
	{
		OnEventBeginOverlap.Broadcast(UKismetMathLibrary::RandomIntegerInRange(0, 2));
	}
}
