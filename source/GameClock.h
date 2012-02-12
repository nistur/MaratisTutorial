#ifndef __GAME_CLOCK_H__
#define __GAME_CLOCK_H__

#include <vector>

class Timer;

//--------------------------------------------
// typedef's
//--------------------------------------------
typedef long int clocktime;

//--------------------------------------------
// GameClock
//
// Takes care of any active timers, also
// provides an interface for getting the delta
// between ticks
//--------------------------------------------
class GameClock
{
public:
	GameClock();
	
	//----------------------------------------
	// Public interface
	//----------------------------------------
	void	Update();

	Timer*		CreateTimer(int id);
	void		DestroyTimer(Timer* timer);

	clocktime	GetDeltaMs();

private:
	//----------------------------------------
	// Internal types
	//----------------------------------------
	typedef std::vector<Timer*> timerVec;
	typedef timerVec::iterator	timerVecIter;
	
	//----------------------------------------
	// Members
	//----------------------------------------
	timerVec	m_Timers;

	clocktime	m_StartTime;
	clocktime	m_CurTime;
	clocktime	m_Delta;
};

#endif /*__GAME_CLOCK_H__*/