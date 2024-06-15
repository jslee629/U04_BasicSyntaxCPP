#include "WChest.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "WPlayer.h"

AWChest::AWChest()
{
	// initialize Emissive
	Emissive = FLinearColor::Red;

	// Make RootComponent
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = RootComp;

	// Make StaticMeshes
	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestTop"));
	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBottom"));

	// Attach ChestTop, ChestBottom Mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> TopAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestTop.SM_ChestTop'"));
	if (TopAsset.Succeeded())
	{
		ChestTop->SetStaticMesh(TopAsset.Object);
		ChestTop->SetupAttachment(RootComp);
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> BottomAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestBottom.SM_ChestBottom'"));
	if (BottomAsset.Succeeded())
	{
		ChestBottom->SetStaticMesh(BottomAsset.Object);
		ChestBottom->SetupAttachment(RootComp);
	}
}

void AWChest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// StaticLoadObject and get material asset
	UObject* Asset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Chest/MI_Chest.MI_Chest'"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(Asset);

	// Create Dynamic material instance
	if (MaterialAsset)
	{
		ChestMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
		ChestTop->SetMaterial(0, ChestMaterial);
		ChestBottom->SetMaterial(0, ChestMaterial);
		ChestMaterial->SetVectorParameterValue("Emissive", Emissive);
	}
}

void AWChest::BeginPlay()
{
	Super::BeginPlay();


}

void AWChest::OpenTheChest()
{
	if (!CanOpen) return;

	ChestTop->SetRelativeRotation(FRotator(45.f, 0, 0));
	AWPlayer* Player = Cast<AWPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		if (Emissive == FLinearColor::Red)
		{
			Player->RedKey += 1;
			CLog::Print("Player Red Key: " + FString::FromInt(Player->RedKey));
		}
		else if (Emissive == FLinearColor::Blue)
		{
			Player->BlueKey += 1;
			CLog::Print("Player Blue Key: " + FString::FromInt(Player->BlueKey));
		}
		else if (Emissive == FLinearColor::Green)
		{
			Player->GreenKey += 1;
			CLog::Print("Player Green Key: " + FString::FromInt(Player->GreenKey));
		}
	}
}

