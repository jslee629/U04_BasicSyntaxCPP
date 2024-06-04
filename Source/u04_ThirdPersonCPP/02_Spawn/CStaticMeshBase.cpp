#include "CStaticMeshBase.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h"

ACStaticMeshBase::ACStaticMeshBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");	// 생성자에서만 쓸 수 있음
	SetRootComponent(MeshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	if (meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}

void ACStaticMeshBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Materials/MI_StaticMesh_Inst")));
	if (materialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, this);
		MeshComp->SetMaterial(0, DynamicMaterial);
	}
	//C++ T::StaticClass()
	//Asset CHelpers::FClassFinder

	UKismetSystemLibrary::K2_SetTimer(this, "UpdateParameters", 1.f, true);
}

void ACStaticMeshBase::UpdateParameters()
{
	//TODO: 랜덤 함수 활용하여 랜덤 상수 하나 뽑아내기
	DynamicMaterial->SetVectorParameterValue("BaseColor", )
}


