#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WDoor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API AWDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OpenTheDoor(AActor* OverlappedActor, AActor* OtherActor);

public:
	UPROPERTY(BlueprintReadOnly)
	bool IsOpen;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Door;
	UBoxComponent* Box;
	UMaterialInstanceDynamic* DoorFrameMaterial;
	UMaterialInstanceDynamic* DoorMaterial;
	UPROPERTY(EditInstanceOnly, Category = "Material Params")
	FLinearColor Color;
	FRotator TargetRotation;
	bool IsMoving;
	float DoorSpeed;
};
