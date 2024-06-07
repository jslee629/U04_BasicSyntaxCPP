#include "CAnimInstance.h"
#include "Global.h"	

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerPawn)
	{
		Speed = OwnerPawn->GetVelocity().Size2D();
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerPawn = TryGetPawnOwner();
}
