#include "u04_ThirdPersonCPPGameModeBase.h"

Au04_ThirdPersonCPPGameModeBase::Au04_ThirdPersonCPPGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
	{
		DefaultPawnClass = pawnAsset.Class;
	}
}
