/* TutorialBehaviour.h
  version 0.0.1, February 12th, 2012

  Copyright (C) 2012 Philipp Geyer

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Philipp Geyer
*/

#ifndef __TUTORIAL_BEHAVIOUR_H__
#define __TUTORIAL_BEHAVIOUR_H__

#include "Timer.h"

#include <MEngine.h>

//--------------------------------------------
// TutorialBehaviour
// 
// Will give our happy little cube some
// character
//--------------------------------------------
class TutorialBehaviour : public MBehavior, public ITimerAction
{
public:
	TutorialBehaviour(MObject3d * parentObject);
	TutorialBehaviour(TutorialBehaviour & behavior, MObject3d * parentObject);
	~TutorialBehaviour();
	
	//----------------------------------------
	// MBehavior virtuals
	//----------------------------------------
	void destroy();
	static MBehavior* getNew(MObject3d* parentObject);
	MBehavior* getCopy(MObject3d* parentObject);

	static const char* getStaticName() { return "Tutorial Controller"; }
	const char* getName() { return getStaticName(); }

	unsigned int getVariablesNumber();
	MVariable getVariable(unsigned int id);

	void update();
	void runEvent(int param){}

	//----------------------------------------
	// ITimerAction virtuals
	//----------------------------------------
	void OnTimerComplete(int id);

private:
	// timers
	enum 
	{
		eBounceTimer,
	};

	// Exposed values
	float		m_RangeX;
	float		m_StepX;
	float		m_RangeZ;
	float		m_StepZ;

	// Member variables
	float		m_CurrDeltaX;
	float		m_CurrDeltaZ;
	MVector3	m_RootPosition;
	Timer*		m_BounceTimer;
	bool		m_IsBouncing;

	// Private interface
	void Setup(float step, float delta, float range);
};

#endif /*__TUTORIAL_BEHAVIOUR_H__*/