#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "WOpener.generated.h"

class AWChest;

UCLASS()
class U04_THIRDPERSONCPP_API AWOpener : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	UPROPERTY(EditAnywhere)
	AWChest* Chest;
};
