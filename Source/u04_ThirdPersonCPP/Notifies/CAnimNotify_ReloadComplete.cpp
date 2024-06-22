#include "CAnimNotify_ReloadComplete.h"
#include "CWeapon.h"
#include "CWeaponInterface.h"

FString UCAnimNotify_ReloadComplete::GetNotifyName_Implementation() const
{
	return "ReloadComplete";
}

void UCAnimNotify_ReloadComplete::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->SetbReloading(false);
}
