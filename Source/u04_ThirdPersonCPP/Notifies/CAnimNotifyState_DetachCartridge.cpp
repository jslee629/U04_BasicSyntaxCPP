#include "CAnimNotifyState_DetachCartridge.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"
#include "CPlayer.h"

FString UCAnimNotifyState_DetachCartridge::GetNotifyName_Implementation() const
{
	return "DetachCartridge";
}

void UCAnimNotifyState_DetachCartridge::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->Begin_Reload();

	ACPlayer* Player = Cast<ACPlayer>(ImplementedOwner);
	if (Player == nullptr) return;

	Player->SpawnCartridge();
}

void UCAnimNotifyState_DetachCartridge::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(ImplementedOwner);
	if (Player == nullptr) return;

	Player->DiscardCartridge();
}
