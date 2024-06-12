#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

class AStaticMeshActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraced, AActor*, InActor, FLinearColor, InColor);

UCLASS()
class U04_THIRDPERSONCPP_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void RagDoll(AActor* InActor, FLinearColor InColor);

private:
	UPROPERTY(EditInstanceOnly)
	AStaticMeshActor* Verticies[2];

public:
	UPROPERTY(BlueprintAssignable)
	FLineTraced OnLineTraced;
};
