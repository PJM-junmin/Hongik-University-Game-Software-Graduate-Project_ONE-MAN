// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/OMEnumTypes.h"
#include "OMFunctionLibrary.generated.h"

class UOMAbilitySystemComponent;
class UPawnCombatComponent;
class UOMGameInstance;
struct FScalableFloat;


/**
 * 
 */
UCLASS()
class ONEMAN_API UOMFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	static UOMAbilitySystemComponent* NativeGetOMASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);


	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);


	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);


	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EOMConfirmType& OutConfirmType);


	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);


	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EOMValidType& OutValidType);


	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.0f);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(Blueprintcallable, Category = "FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* inInstigator, AActor* inTargetActor, const FGameplayEffectSpecHandle& inSpecHandle);

	// CountDown
	UFUNCTION(Blueprintcallable, Category = "FunctionLibrary", meta = (Latent, WorldContext = "worldContextObject", 
		LatentInfo = "latentInfo", ExpandEnumAsExecs = "countDownInput|countDownOutput", totalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* worldContextObject, float totalTime, float updateInterval, 
		float& outRemainingTime, EOMCountDownActionInput countDownInput, 
		UPARAM(DisplayName = "Output")EOMCountDownActionOutput& countDownOutput, FLatentActionInfo latentInfo);


	// GameInstance
	UFUNCTION(BlueprintPure, Category = "FunctionLibrary", meta = (WorldContext = "worldContextObject"))
	static UOMGameInstance* GetOMGameInstance(const UObject* worldContextObject);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (WorldContext = "worldContextObject"))
	static void ToggleInputMode(const UObject* worldContextObject, EOMInputMode InInputMode);

	// SaveGame
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void SaveCurrentGameDifficulty(EOMGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(EOMGameDifficulty& outSavedDifficulty);


};
