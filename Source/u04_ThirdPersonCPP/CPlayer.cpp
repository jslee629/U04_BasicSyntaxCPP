#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CAnimInstance.h"
#include "CWeapon.h"
#include "Widgets/CCrossHairWidget.h"
#include "Widgets/CWeaponWidget.h"

ACPlayer::ACPlayer()
{
	// 캐릭터에 스프링암과 카메라 부착
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	// UseControllerRotationYaw랑 OrientRotationToMovement는 짝꿍
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// 마네킹 메시 붙이기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Character/Mesh/SK_Mannequin"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));
	}

	// 애니메이션 넣어주기
	ConstructorHelpers::FClassFinder<UCAnimInstance> AnimInstanceClass(TEXT("/Game/ABP_Cplayer"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}

	// 에임위젯 넣어주기
	ConstructorHelpers::FClassFinder<UCCrossHairWidget> CrossHairWidgetClassAsset(TEXT("/Game/Widgets/WB_Crosshair"));
	if (CrossHairWidgetClassAsset.Succeeded())
	{
		CrossHairWidgetClass = CrossHairWidgetClassAsset.Class;
	}

	// 웨폰위젯 넣어주기
	ConstructorHelpers::FClassFinder<UCWeaponWidget> WeaponWidgetClassAsset(TEXT("/Game/Widgets/WB_Weapon"));
	if (WeaponWidgetClassAsset.Succeeded())
	{
		WeaponWidgetClass = WeaponWidgetClassAsset.Class;
	}
}

void ACPlayer::ChangeSpeed(float InMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InMoveSpeed;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), this);

	if (ensure(BodyMaterial) && ensure(LogoMaterial))
	{
		GetMesh()->SetMaterial(0, BodyMaterial);
		GetMesh()->SetMaterial(1, LogoMaterial);
	}

	// 무기 스폰
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Weapon = GetWorld()->SpawnActor<ACWeapon>(WeaponClass, SpawnParam);

	// 에임위젯 스폰
	CrossHairWidget = CreateWidget<UCCrossHairWidget, APlayerController>(GetController<APlayerController>(), CrossHairWidgetClass);
	CrossHairWidget->AddToViewport();
	CrossHairWidget->SetVisibility(ESlateVisibility::Hidden);

	// 웨폰위젯 스폰
	WeaponWidget = CreateWidget<UCWeaponWidget, APlayerController>(GetController<APlayerController>(), WeaponWidgetClass);
	WeaponWidget->AddToViewport();
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 이벤트 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);

	// 액션 이벤트 바인딩
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::ToggleEquip);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::OnAutoFire);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnTurn(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnLookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::ToggleEquip()
{
	if (Weapon == nullptr) return;

	if (Weapon->IsEquipped())
	{
		OffAim();
		Weapon->Unequip();
		return;
	}

	Weapon->Equip();
}

void ACPlayer::OnAim()
{
	if (Weapon == nullptr) return;

	if (Weapon->IsEquipped() == false) return;
	if (Weapon->IsEquipping() == true) return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	Begin_Zoom();

	Weapon->Begin_Aiming();

	CrossHairWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	Weapon->End_Fire();

	if (Weapon == nullptr) return;

	if (Weapon->IsEquipped() == false) return;
	if (Weapon->IsEquipping() == true) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	End_Zoom();

	Weapon->End_Aiming();

	CrossHairWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnFire()
{
	Weapon->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Weapon->End_Fire();
}

void ACPlayer::OnAutoFire()
{
	if (Weapon->IsFiring() == true) return;
	Weapon->ToggleAutoFire();
	Weapon->IsAutoFire() ? WeaponWidget->OnAutoFire() : WeaponWidget->OffAutoFire();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = CameraComp->GetForwardVector();

	FVector MuzzleLoation = Weapon->GetMesh()->GetSocketLocation("MuzzleFlash");
	FVector CameraLocation = CameraComp->GetComponentToWorld().GetLocation();
	OutAimStart = CameraLocation + OutAimDirection * (OutAimDirection | (MuzzleLoation - CameraLocation));

	FVector RandomConeDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);
	RandomConeDirection *= 50000.f;
	OutAimEnd = CameraLocation + RandomConeDirection;
}

void ACPlayer::OnTarget()
{
	if (CrossHairWidget == nullptr) return;
	CrossHairWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	if (CrossHairWidget == nullptr) return;
	CrossHairWidget->OffTarget();
}

