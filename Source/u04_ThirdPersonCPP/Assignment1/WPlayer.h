#pragma once

#include "CoreMinimal.h"
#include "CPlayer.h"
#include "WPlayer.generated.h"

class AWOpener;

UCLASS()
class U04_THIRDPERSONCPP_API AWPlayer : public ACPlayer
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Open();

public:
	UFUNCTION()
	void SaveOpener(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void RemoveOpener(AActor* OverlappedActor, AActor* OtherActor);

public:
	AWOpener* Opener;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Keys")
	float RedKey = 0.1f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Keys")
	float BlueKey = 0.1f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Keys")
	float GreenKey = 0.1f;
};
