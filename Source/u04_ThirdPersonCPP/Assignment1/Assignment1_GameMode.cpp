#include "Assignment1_GameMode.h"

AAssignment1_GameMode::AAssignment1_GameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Class'/Script/u04_ThirdPersonCPP.WPlayer'"));

	if (pawnAsset.Succeeded())
	{
		DefaultPawnClass = pawnAsset.Class;
	}
}