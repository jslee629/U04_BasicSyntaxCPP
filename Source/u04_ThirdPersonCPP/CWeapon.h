#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;
class UCameraShake;
class ACBullet;
class UParticleSystem;
class USoundCue;
class UMaterialInstanceConstant;

UCLASS()
class U04_THIRDPERSONCPP_API ACWeapon : public AActor
{
	GENERATED_BODY()

public:
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE bool IsReloading() { return bReloading; }
	FORCEINLINE void SetbReloading(bool b) { bReloading = b; }

	void ToggleAutoFire();	// 연사 모드 설정

	void Begin_Aiming();	// setter 에 왠만하면 파라미터 받지 말자
	void End_Aiming();		// setter 에 왠만하면 파라미터 받지 말자

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
	void Firing();

	void Equip();
	void Begin_Equip();		// in notify
	void End_Equip();		// in notify

	void Unequip();
	void Begin_Unequip();	// in notify
	void End_Unequip();		// in notify

	UFUNCTION()
	void Reload();
	void Begin_Reload();
	void End_Reload();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float FireInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterialInstanceConstant* DecalMaterial;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
	bool bAutoFire;
	bool bReloading;

	float CurrentPitch;

	FTimerHandle AutoTimerHandle;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxBulletCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 CurBulletCount;
};
