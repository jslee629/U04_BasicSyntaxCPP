#include "CBoxDelegate.h"

void ACBoxDelegate::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (OnBoxBeginOverlap.IsBound())
	{
		//4. 콜백
		OnBoxBeginOverlap.Execute();
	}

	if (OnBoxOneParam.IsBound())
	{
		//4. 콜백
		FString Str = OnBoxOneParam.Execute(FLinearColor::MakeRandomColor());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Str);
	}
}

void ACBoxDelegate::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);

	if (OnBoxEndOverlap.IsBound())
	{
		//4. 콜백
		OnBoxEndOverlap.Execute();
	}
}
