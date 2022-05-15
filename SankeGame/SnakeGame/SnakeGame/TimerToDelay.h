#pragma once

class TimerToDelay
{
private:
	double timeForDelay;
	double timeForCalculationOfDelay;
public:
	explicit TimerToDelay(const double & _timerForDelay);

	bool isDelaying();
	void decreaseTime(const double& time);
};