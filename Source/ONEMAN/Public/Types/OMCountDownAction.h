// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Types/OMEnumTypes.h"


class FOMCountDownAction : public FPendingLatentAction // 일시 중지 후 이어서 작업
{
public:
	FOMCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EOMCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false),
		totalCountDownTime(InTotalCountDownTime),
		updateInterval(InUpdateInterval),
		outRemainingTime(InOutRemainingTime),
		countDownOutput(InCountDownOutput),
		executionFunction(LatentInfo.ExecutionFunction),
		outputLink(LatentInfo.Linkage),
		callbackTarget(LatentInfo.CallbackTarget),
		elapsedInterval(0.0f),
		elapsedTimeSinceStart(0.0f)
	{
	}

	virtual void UpdateOperation(FLatentResponse& response) override;
	void CancelAction();

private:
	bool bNeedToCancel; // 외부에서 취소 요청할 경우를 대비한 Flag
	float totalCountDownTime; 
	float updateInterval; // update 간격
	float& outRemainingTime; // 남은 시간
	EOMCountDownActionOutput& countDownOutput;
	FName executionFunction;
	int32 outputLink;
	FWeakObjectPtr callbackTarget;
	float elapsedInterval;
	float elapsedTimeSinceStart;

};