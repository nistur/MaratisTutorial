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