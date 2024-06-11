#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLights.generated.h"

class USpotLightComponent;
class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API ACSpotLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLights();

protected:
	virtual void BeginPlay() override;

private:
	void OnLight(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;
	UPROPERTY(VisibleDefaultsOnly)
	USpotLightComponent* SpotLightComps[3];

};
