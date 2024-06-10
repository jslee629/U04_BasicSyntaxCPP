#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxActorOverlap.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxActorOverlap : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
