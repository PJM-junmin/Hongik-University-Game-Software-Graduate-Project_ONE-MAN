// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONEMAN_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()
		

protected:
	template <class T>
	T* GetOwningPawn() const
	{
		// check the T's class and if it's not a APawn's child class, Generate Error
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController() const
	{
		// check the T's class and if it's not a APawn Controller's child class, Generate Error
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter to GetController must be derived from APawn");
		return GetOwningController<APawn>()->GetController<T>();
	}

};
