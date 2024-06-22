#include "CAnimNotifyState_RefillCartridge.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"
#include "CPlayer.h"
#include "CCartridge.h"

FString UCAnimNotifyState_RefillCartridge::GetNotifyName_Implementation() const
{
	return "RefilCartridge";
}

void UCAnimNotifyState_RefillCartridge::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(ImplementedOwner);
	if (Player == nullptr) return;

	Player->SpawnCartridge();
}

void UCAnimNotifyState_RefillCartridge::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->End_Reload();

	ACPlayer* Player = Cast<ACPlayer>(ImplementedOwner);
	if (Player == nullptr) return;

	Player->DestroyCartridge();
}
