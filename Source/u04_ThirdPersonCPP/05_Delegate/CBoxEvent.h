#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxEvent.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxEvent : public ACBoxBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(ACBoxEvent, FEventBeginOverlap, int32);
	FEventBeginOverlap OnEventBeginOverlap;

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
