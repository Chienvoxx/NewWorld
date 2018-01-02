#pragma once
#include <GLFW/glfw3.h>


class Timer
{
public:
	
	// ----
	Timer() : mScaleValue(1.0), mIsStarted(false), mIsPaused(false) {}

	// ------------------------------------------------------
	Timer(double timeScale, bool startTimer, bool pauseTimer) : mScaleValue(timeScale)
	{
		if (startTimer)
			start();
		if (isStarted())
		{
			if (pauseTimer)
				pause();
		}
	}

	// ---------
	void start()
	{
		if (!isStarted())
		{
			mBeginningTime = glfwGetTime();
			mIsStarted = true;
			mIsPaused = false;
			// This timer may have been stopped and is now being restarted
			// reset all values
			mLastTime = 0.0;
			mLastTickTime = 0.0;
			mDeltaTime = 0.0;
			mAccumulateTime = 0.0;
			mAccumulateTicks = 0.0;
			mPauseTime = 0.0;
			mStopTime = 0.0;
		}
	}

	//---------
	void stop()
	{
		// Stop if started and un-pause if paused
		if (mIsStarted)
			mIsStarted = false;
		if (mIsPaused)
			mIsPaused = false;
		mStopTime = glfwGetTime();
		mAccumulateTime += mStopTime - mLastTime;
	}

	// -------------
	bool isStarted()
	{
		return mIsStarted;
	}

	// ---------
	void pause()
	{
		if (mIsStarted)
		{
			if (mIsPaused)
				mIsPaused = false;
			else
			{
				mIsPaused = true;
				mPauseTime = getTime();
			}
		}
	}

	// ------------
	bool isPaused()
	{
		if (mIsStarted)
			return mIsPaused;
	}

	// -------------
	// If timer is started and not puased
	// Returns current clock time
	// Otherwise returns 0.0
	double getTime()
	{
		double newTime = 0.0;
		if (mIsStarted)
		{
			if (!mIsPaused)
			{
				newTime = glfwGetTime();
				mAccumulateTime += newTime - mLastTime;
				mLastTime = newTime;
			}
		}
		return newTime;
	}

	// ------------------
	double getDeltaTime()
	{

	}

	// ------------------
	double getStartTime()
	{
		return mBeginningTime;
	}

	// --------------------
	// Clock time since the timer was started minus paused time
	double getRunningTime()
	{
		// update accumulator and return
		getTime();
		return mAccumulateTime;
	}

	// ------------------------------
	// Change the ratio of ticks to real time.
	void scaleTime(double scaleValue)
	{
		mScaleValue = scaleValue;
	}

	// --------------
	// Number of ticks since this was last called
	double getTicks()
	{
		mGetTickCounter++;
		// update timer; claculate, add, and return ticks
		double t = getTime();
		mDeltaTime = t - mLastTickTime;
		//if (mGetTickCounter % 36 == 0)
		//	bool debug = true;
		mLastTickTime = t;
		double ticks = mDeltaTime * mScaleValue;
		mAccumulateTicks += ticks;
		return ticks;
	}

private:
	double mBeginningTime = 0.0;
	double mLastTime = 0.0;
	double mLastTickTime = 0.0;
	double mDeltaTime = 0.0; // used to calculate ticks
	double mAccumulateTime = 0.0;
	double mAccumulateTicks = 0.0;

	double mPauseTime = 0.0;
	double mStopTime = 0.0;
	double mScaleValue = 1.0; // 100% if real time
	bool mIsStarted = false;
	bool mIsPaused = false;

	int mGetTickCounter = 0;
};
