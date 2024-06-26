#include "CAnimInstance.h"
#include "Global.h"	
#include "CWeaponInterface.h"
#include "CWeapon.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerPawn)
	{
		Speed = OwnerPawn->GetVelocity().Size2D();
		Direction = CalculateDirection(OwnerPawn->GetVelocity(), OwnerPawn->GetControlRotation());
		Pitch = OwnerPawn->GetBaseAimRotation().Pitch;

		ICWeaponInterface* ImplementedPawn = Cast<ICWeaponInterface>(OwnerPawn);
		if (ImplementedPawn)
		{
			ACWeapon* Weapon = ImplementedPawn->GetWeapon();
			if (Weapon)
			{
				bEquipped = Weapon->IsEquipped();
				bAiming = Weapon->IsAiming();
			}
		}
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerPawn = TryGetPawnOwner();
}
