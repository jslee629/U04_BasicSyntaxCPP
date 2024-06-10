#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxDelegate.generated.h"

//1. 델리게이트 타입의 선언
DECLARE_DELEGATE(FBoxBeginOverlap);
DECLARE_DELEGATE(FBoxEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxOneParam, FLinearColor);

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxDelegate : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	//2. 델리게이트 변수의 선언
	FBoxBeginOverlap OnBoxBeginOverlap;
	FBoxEndOverlap OnBoxEndOverlap;
	FBoxOneParam OnBoxOneParam;
};
