#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshBase.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACStaticMeshBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMeshBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)		// TODO: 이거 Anywhere말고 딴 걸로 바꿔야함
	UStaticMeshComponent* MeshComp;

};
