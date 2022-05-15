#include "TimerToDelay.h"
TimerToDelay::TimerToDelay(const double& _timerForDelay) : timeForDelay(_timerForDelay), timeForCalculationOfDelay(_timerForDelay)
{
}

bool TimerToDelay::isDelaying()
{
	if (this->timeForCalculationOfDelay <= 0.0)
	{
		this->timeForCalculationOfDelay = this->timeForDelay;
		return false;
	}
	else
	{
		return true;
	}
}

void TimerToDelay::decreaseTime(const double& time)
{
	this->timeForCalculationOfDelay -= time;
}
