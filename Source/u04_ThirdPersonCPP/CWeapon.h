#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;

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
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }

	void Begin_Aiming();	// setter �� �ظ��ϸ� �Ķ���� ���� ����
	void End_Aiming();		// setter �� �ظ��ϸ� �Ķ���� ���� ����

	void Equip();
	void Begin_Equip();		// in notify
	void End_Equip();		// in notify
	void Unequip();
	void Begin_Unequip();	// in notify
	void End_Unequip();		// in notify

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnequipMontage;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
};