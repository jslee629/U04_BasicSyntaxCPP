#include "CStaticMeshCone.h"

ACStaticMeshCone::ACStaticMeshCone()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cone"));
	if (meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}