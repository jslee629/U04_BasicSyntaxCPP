#include "WDoor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "WPlayer.h"

AWDoor::AWDoor()
	: IsOpen(false), IsMoving(false), DoorSpeed(2.f)
{
	PrimaryActorTick.bCanEverTick = true;

	// Make RootComponent
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = RootComp;

	// Make StaticMeshes
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	// Make BoxComponent
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));

	// Attach DoorFrame, Door Mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorFrameAsset(TEXT("StaticMesh'/Game/Assignment1/Door/Props/SM_DoorFrame.SM_DoorFrame'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("StaticMesh'/Game/Assignment1/Door/Props/SM_Door.SM_Door'"));
	DoorFrame->SetStaticMesh(DoorFrameAsset.Object);
	Door->SetStaticMesh(DoorAsset.Object);
	DoorFrame->SetupAttachment(RootComp);
	Door->SetupAttachment(RootComp);
	DoorFrame->SetRelativeLocation(FVector(0, -44.f, 0));

	// Attach Box
	Box->SetupAttachment(RootComp);
	Box->SetRelativeLocation(FVector(0, -40.f, 108.f));
}

void AWDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// StaticLoadObject and get material asset
	UObject* Asset_DoorFrame = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment1/Door/Materials/MI_Frame.MI_Frame'"));
	UMaterialInstanceConstant* MaterialAsset_DoorFrame = Cast<UMaterialInstanceConstant>(Asset_DoorFrame);
	UObject* Asset_Door = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment1/Door/Materials/MI_Door.MI_Door'"));
	UMaterialInstanceConstant* MaterialAsset_Door = Cast<UMaterialInstanceConstant>(Asset_Door);

	// Create Dynamic material instance
	if (MaterialAsset_DoorFrame)
	{
		DoorFrameMaterial = UMaterialInstanceDynamic::Create(MaterialAsset_DoorFrame, nullptr);
		DoorFrame->SetMaterial(0, DoorFrameMaterial);
		DoorFrameMaterial->SetVectorParameterValue("Color", Color);
	}
	if (MaterialAsset_Door)
	{
		DoorMaterial = UMaterialInstanceDynamic::Create(MaterialAsset_Door, nullptr);
		Door->SetMaterial(0, DoorMaterial);
		DoorMaterial->SetVectorParameterValue("Color", Color);
	}
}

void AWDoor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AWDoor::OpenTheDoor);

	TargetRotation = Door->GetRelativeRotation() + FRotator(0, 90.f, 0);
}

void AWDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMoving)
	{
		FRotator CurrentRotation = Door->GetRelativeRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, DoorSpeed);

		Door->SetRelativeRotation(NewRotation);

		if (CurrentRotation.Equals(TargetRotation, 1.0f))
		{
			IsMoving = false;
		}
	}
}

void AWDoor::OpenTheDoor_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Log("Door Overlapped");

	AWPlayer* Player = Cast<AWPlayer>(OtherActor);
	if (Player)
	{
		if (Color == FLinearColor::Red)
		{
			if (Player->RedKey != 1.f)
			{
				IsOpen == false ? DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 200.f), TEXT("You have no Red key"), nullptr, FColor::Red, 3.f) : nullptr;
			}
			else
			{
				Player->RedKey = 0.1f;
				IsMoving = true;
				IsOpen = true;
			}
		}
		else if (Color == FLinearColor::Blue)
		{
			if (Player->BlueKey != 1.f)
			{
				IsOpen == false ? DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 200.f), TEXT("You have no Blue key"), nullptr, FColor::Blue, 3.f) : nullptr;
			}
			else
			{
				Player->BlueKey = 0.1f;
				IsMoving = true;
				IsOpen = true;
			}
		}
		else if (Color == FLinearColor::Green)
		{
			if (Player->GreenKey != 1.f)
			{
				IsOpen == false ? DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 200.f), TEXT("You have no Green key"), nullptr, FColor::Green, 3.f) : nullptr;
			}
			else
			{
				Player->GreenKey = 0.1f;
				IsMoving = true;
				IsOpen = true;
			}
		}
	}
}
