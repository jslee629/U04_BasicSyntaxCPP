#include "CBoxActorOverlap.h"
#include "Global.h"

void ACBoxActorOverlap::BeginPlay()
{
	Super::BeginPlay();

}

void ACBoxActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);
	CLog::Print("OtherActor: " + OtherActor->GetActorLabel());
}
