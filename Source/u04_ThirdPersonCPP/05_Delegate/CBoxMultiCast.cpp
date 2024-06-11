#include "CBoxMultiCast.h"
#include "Global.h"

void ACBoxMultiCast::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (OnMultiCastBeginOverlap.IsBound())
	{
		int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		FLinearColor RandomColor = FLinearColor::MakeRandomColor();

		OnMultiCastBeginOverlap.Broadcast(RandomIndex, RandomColor);
	}
}