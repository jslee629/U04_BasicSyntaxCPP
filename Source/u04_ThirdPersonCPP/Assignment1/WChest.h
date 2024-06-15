#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WChest.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API AWChest : public AActor
{
	GENERATED_BODY()
	
public:	
	AWChest();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	void OpenTheChest();

private:
	USceneComponent* RootComp;
	UStaticMeshComponent* ChestTop;
	UStaticMeshComponent* ChestBottom;
	UMaterialInstanceDynamic* ChestMaterial;
	UPROPERTY(EditInstanceOnly, Category = "Material Params")
	FLinearColor Emissive;

public:
	bool CanOpen;
};
