#ifndef __TIMER_H__
#define __TIMER_H__

#include "GameClock.h"

//--------------------------------------------
// ITimerAction
//
// Command pattern. Timer callback.
//--------------------------------------------
class ITimerAction
{
public:
	virtual void OnTimerComplete(int id) = 0;
};

#include <vector>

//--------------------------------------------
// Timer
//
// Class to count down to an event.
//--------------------------------------------
class Timer
{
public:
	Timer(int id);

	//----------------------------------------
	// Public interface
	//----------------------------------------
	// Start/stop the timer. Won't affect
	// the time remaining
	void		Start();
	void		Stop();

	// Check whether the timer is still running.
	// Can be not running but not expired.
	bool		IsRunning();

	void		SetTimeMs(clocktime ms);
	clocktime	GetTimeRemaining();
	bool		HasExpired();

	// Action interface
	void AddAction(ITimerAction* action);
	void RemoveAction(ITimerAction* action);
	
	void		Update(clocktime dt);
private:
	// internal types
	typedef std::vector<ITimerAction*>	actionVec;
	typedef actionVec::iterator			actionVecIter;

	actionVec	m_Actions;

	clocktime	m_TimeMs;
	bool		m_IsRunning;

	// every Timer used by a class should have a
	// different ID. It's only used for letting
	// the action know which timer has expired
	// so there's no need for the id to be
	// unique across the whole system.
	int			m_ID;
};

#endif /*__TIMER_H__*/