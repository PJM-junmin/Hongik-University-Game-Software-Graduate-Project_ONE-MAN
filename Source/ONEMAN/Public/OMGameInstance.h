// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "OMGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FOMGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Gategories = "GameData.Level"))
	FGameplayTag levelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> level;

	bool IsValid() const
	{
		return levelTag.IsValid() && !level.IsNull();
	}

};

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	virtual void Init() override;

protected:
	virtual void OnPreLoadMap(const FString& mapName);
	virtual void OnDestinationWorldLoaded(UWorld* loadedWorld);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FOMGameLevelSet> gameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

};
