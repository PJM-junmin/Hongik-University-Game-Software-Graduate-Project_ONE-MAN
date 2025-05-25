// Vince Petrelli all Rights Reserved


#include "OMGameInstance.h"
#include "MoviePlayer.h"

void UOMGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);

}

void UOMGameInstance::OnPreLoadMap(const FString& mapName)
{
	FLoadingScreenAttributes loadingScreenAttributes;
	loadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	loadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.0f;
	loadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(loadingScreenAttributes);

}

void UOMGameInstance::OnDestinationWorldLoaded(UWorld* loadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

TSoftObjectPtr<UWorld> UOMGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FOMGameLevelSet& gameLevelSet : gameLevelSets)
	{
		if (!gameLevelSet.IsValid()) 
			continue;

		if (gameLevelSet.levelTag == InTag)
		{
			return gameLevelSet.level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
