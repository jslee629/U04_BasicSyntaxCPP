#include "CCubes.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxMultiCast.h"

ACCubes::ACCubes()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'"));

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("MeshComp");
		Str.Append(FString::FromInt(i+1));
		MeshComp[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(Str));

		MeshComp[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		MeshComp[i]->SetSimulatePhysics(false);

		if (MeshAsset.Succeeded())
		{
			MeshComp[i]->SetStaticMesh(MeshAsset.Object);
		}

		MeshComp[i]->SetupAttachment(RootComp);
	}


}

void ACCubes::BeginPlay()
{
	Super::BeginPlay();

	UObject* ContentAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Materials/MI_StaticMesh_Inst.MI_StaticMesh_Inst'"));
	UMaterialInstanceConstant* MaterialAsset = Cast< UMaterialInstanceConstant>(ContentAsset);

	for (int32 i = 0; i < 3; i++)
	{
		if (MaterialAsset)
		{
			DynamicMaterials[i] = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
			MeshComp[i]->SetMaterial(0, DynamicMaterials[i]);
			
			FTransform WorldTransform = MeshComp[i]->GetComponentToWorld();
			OriginLocations[i] = WorldTransform.GetLocation();
		}
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxMultiCast::StaticClass(), Actors);

	if (Actors.Num() < 1) return;

	ACBoxMultiCast* Trigger = Cast<ACBoxMultiCast>(Actors[0]);
	if (Trigger)
	{
		Trigger->OnMultiCastBeginOverlap.AddUObject(this, &ACCubes::Drop);
	}
}

void ACCubes::Drop(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FLinearColor::White);
		MeshComp[i]->SetSimulatePhysics(false);
		MeshComp[i]->SetWorldLocation(OriginLocations[i]);
	}
	MeshComp[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}


