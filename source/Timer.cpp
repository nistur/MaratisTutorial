#include "Timer.h"

#include <algorithm>

//----------------------------------------
// Timer
//----------------------------------------
Timer::Timer(int id)
:m_ID(id)
,m_IsRunning(true)
{
}
//----------------------------------------
void Timer::Start()
{
	m_IsRunning = true;
}
//----------------------------------------
void Timer::Stop()
{
	m_IsRunning = false;
}
//----------------------------------------
bool Timer::IsRunning()
{
	return m_IsRunning;
}
//----------------------------------------
void Timer::Update(clocktime dt)
{
	if(m_IsRunning && m_TimeMs > 0)
	{
		// tick the timer
		m_TimeMs -= dt;

		// check if we've expired
		if(m_TimeMs < 0)
		{
			// make sure the timer doesn't
			// get below 0
			m_TimeMs = 0;

			// let any attached actions know
			actionVecIter iAction;
			for(iAction = m_Actions.begin();
				iAction != m_Actions.end();
				iAction++)
			{
				(*iAction)->OnTimerComplete(m_ID);
			}
			m_IsRunning = false;
		}
	}
}
//----------------------------------------
void Timer::SetTimeMs(clocktime ms)
{
	m_TimeMs = ms;
}
//----------------------------------------
clocktime Timer::GetTimeRemaining()
{
	return m_TimeMs;
}
//----------------------------------------
bool Timer::HasExpired()
{
	return m_TimeMs <= 0;
}
//----------------------------------------
void Timer::AddAction(ITimerAction* action)
{
	// make sure that we haven't already
	// added this action, otherwise we
	// would get OnTimerComplete called
	// multiple times
	if(std::find(	m_Actions.begin(),
					m_Actions.end(), 
					action) == m_Actions.end())
	{
		m_Actions.push_back(action);
	}
}
//----------------------------------------
void Timer::RemoveAction(ITimerAction* action)
{
	// lookup the action and remove
	actionVecIter iAction = 
		std::find(	m_Actions.begin(),
					m_Actions.end(), 
					action);
	if(iAction != m_Actions.end())
	{
		m_Actions.erase(iAction);
	}
}