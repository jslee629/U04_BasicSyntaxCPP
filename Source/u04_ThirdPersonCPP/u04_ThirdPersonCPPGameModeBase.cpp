#include "u04_ThirdPersonCPPGameModeBase.h"

Au04_ThirdPersonCPPGameModeBase::Au04_ThirdPersonCPPGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("/Game/BP_CPlayer"));

	if (pawnAsset.Succeeded())
	{
		DefaultPawnClass = pawnAsset.Class;
	}
}
