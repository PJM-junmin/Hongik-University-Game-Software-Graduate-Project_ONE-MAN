// Vince Petrelli all Rights Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/OMAttributeSet.h"
#include "OMGameplayTags.h"

// Debug Helper
#include "OMDebugHelper.h"

struct FOMDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FOMDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOMAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOMAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOMAttributeSet, DamageTaken, Target, false)
	}
};

static const FOMDamageCapture& GetOMDamageCapture()
{
	static FOMDamageCapture OMDamageCapture;
	return OMDamageCapture;
}

// Setup Calculate AttributeSet
UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	// Slow way of doing capture
	/*FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
		UOMAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UOMAttributeSet, AttackPower)
	);

	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
		AttackPowerProperty,
		EGameplayEffectAttributeCaptureSource::Source,
		false
	);

	RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);*/

	RelevantAttributesToCapture.Add(GetOMDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetOMDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetOMDamageCapture().DamageTakenDef);
}

// Calculate Dynamic AttributeSet
void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	/*EffectSpec.GetContext().GetSourceObject();
	EffectSpec.GetContext().GetAbility();
	EffectSpec.GetContext().GetInstigator();
	EffectSpec.GetContext().GetEffectCauser();*/

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetOMDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	// Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);


	float BaseDamage = 0.0f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(OMGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(OMGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}

		if (TagMagnitude.Key.MatchesTagExact(OMGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}

	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetOMDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	// Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		// increaseDamage 5% in each Combo
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.0f;

		BaseDamage *= DamageIncreasePercentLight;
		// Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		// increaseDamage 20% in each Combo
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount - 1) * 0.2f + 1.0f;

		BaseDamage *= DamageIncreasePercentHeavy;
		// Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetOMDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
