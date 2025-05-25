// Vince Petrelli all Rights Reserved


#include "Types/OMCountDownAction.h"

void FOMCountDownAction::UpdateOperation(FLatentResponse& response)
{
	if (bNeedToCancel)
	{
		countDownOutput = EOMCountDownActionOutput::Cancelled;

		response.FinishAndTriggerIf(true, executionFunction, outputLink, callbackTarget);

		return;
	}

	if (elapsedTimeSinceStart >= totalCountDownTime)
	{
		countDownOutput = EOMCountDownActionOutput::Completed;

		response.FinishAndTriggerIf(true, executionFunction, outputLink, callbackTarget);

		return;
	}

	if (elapsedInterval < updateInterval)
	{
		elapsedInterval += response.ElapsedTime();
	}
	else
	{
		elapsedTimeSinceStart += updateInterval > 0.0f ? updateInterval : response.ElapsedTime();
		outRemainingTime = totalCountDownTime - elapsedTimeSinceStart;
		countDownOutput = EOMCountDownActionOutput::Updated;

		response.TriggerLink(executionFunction, outputLink, callbackTarget);

		elapsedInterval = 0.0f;
	}
}

void FOMCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}


