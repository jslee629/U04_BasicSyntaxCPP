#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCartridge.generated.h"

class UStaticMeshComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACCartridge : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCartridge();

protected:
	virtual void BeginPlay() override;

private:
	UStaticMeshComponent* MeshComp;
};
