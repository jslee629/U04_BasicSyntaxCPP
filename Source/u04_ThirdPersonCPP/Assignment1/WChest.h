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
	UFUNCTION(BlueprintNativeEvent)
	void OpenTheChest();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestTop;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestBottom;
	UMaterialInstanceDynamic* ChestMaterial;
	UPROPERTY(EditInstanceOnly, Category = "Material Params")
	FLinearColor Emissive;

public:
	bool CanOpen;
};
