#include "CStaticMesh_Spawner.h"
#include "CStaticMeshBase.h"

ACStaticMesh_Spawner::ACStaticMesh_Spawner()
{

}

void ACStaticMesh_Spawner::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 4; i++)
	{
		FTransform transform;

		FVector location = GetActorLocation();
		SpawnedObjects[i] = GetWorld()->SpawnActor<ACStaticMeshBase>(SpawnClasses[i], transform);

		SpawnedObjects[i]->SetActorLocation(FVector(location.X, location.Y + i * 200, location.Z));
		//Incomplete... �̷� ������ ���� ������ ����� �����
	}
}


