#include "GameClock.h"

#include "Timer.h"

#include <algorithm>
#include <MEngine.h>

//----------------------------------------
// getCurTime
// quick helper function to lookup tick
// time
//----------------------------------------
clocktime getCurTime()
{
	MEngine* engine = MEngine::getInstance();
	MSystemContext* system = engine->getSystemContext();

	return system->getSystemTick();
}

//----------------------------------------
GameClock::GameClock()
{
	m_StartTime = getCurTime();
	m_CurTime = m_StartTime;
	m_Delta = 0;
}
//----------------------------------------
void GameClock::Update()
{
	// get the new time and then work out the delta
	clocktime prevTime = m_CurTime;
	m_CurTime = getCurTime();
	m_Delta = m_CurTime - prevTime;

	// update any attached timers
	for(timerVecIter iTimer = m_Timers.begin(); 
		iTimer != m_Timers.end(); 
		iTimer++)
	{
		(*iTimer)->Update(m_Delta);
	}
}
//----------------------------------------
Timer* GameClock::CreateTimer(int id)
{
	// create a new timer and push it
	// back onto the update list
	Timer* timer = new Timer(id);
	m_Timers.push_back(timer);
	return timer;
}
//----------------------------------------
void GameClock::DestroyTimer(Timer* timer)
{
	// try to find the timer and remove from
	// the update list
	timerVecIter iTimer = std::find(m_Timers.begin(), 
									m_Timers.end(), 
									timer);
	if(iTimer != m_Timers.end())
	{
		m_Timers.erase(iTimer);
	}

	// regardless of whether it was in the
	// list, we need to delete the timer
	delete timer;
}
//----------------------------------------
clocktime GameClock::GetDeltaMs()
{
	return m_Delta;
}