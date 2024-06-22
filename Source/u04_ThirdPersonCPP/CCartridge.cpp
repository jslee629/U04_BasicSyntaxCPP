#include "CCartridge.h"
#include "Components/StaticMeshComponent.h"

ACCartridge::ACCartridge()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> CartridgeAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty"));
	if (CartridgeAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(CartridgeAsset.Object);
	}

}

void ACCartridge::BeginPlay()
{
	Super::BeginPlay();
	
}

