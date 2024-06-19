#include "CBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACBullet::ACBullet()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MaterialAsset(TEXT("/Game/Materials/MI_Bullet_Inst"));
	if (MaterialAsset.Succeeded())
	{
		MeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	MeshComp->SetRelativeScale3D(FVector(1.f, 0.025f, 0.025f));
	MeshComp->CastShadow = 0;
	SetActorEnableCollision(false);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileComp->InitialSpeed = 2e+4f;
	ProjectileComp->MaxSpeed = 2e+4f;
	ProjectileComp->ProjectileGravityScale = 0;



}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.f);
}