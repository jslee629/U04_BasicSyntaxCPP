#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxMultiCast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiCastBeginOverlap, int32, FLinearColor);

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxMultiCast : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	//virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	FMultiCastBeginOverlap OnMultiCastBeginOverlap;
};
