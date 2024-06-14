#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapon;

UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400);

	FORCEINLINE ACWeapon* GetWeapon() override { return Weapon; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin_Zoom();
	UFUNCTION(BlueprintImplementableEvent)
	void End_Zoom();

protected:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnTurn(float Axis);
	void OnLookUp(float Axis);

	void ToggleEquip();

	void OnAim();
	void OffAim();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(EditDefaultsOnly, Category="WeaponClass")
	TSubclassOf<ACWeapon> WeaponClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapon* Weapon;
};
