#include "CStaticMeshCylinder.h"

ACStaticMeshCylinder::ACStaticMeshCylinder()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cylinder"));
	if (meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}