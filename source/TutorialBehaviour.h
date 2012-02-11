#ifndef __TUTORIAL_BEHAVIOUR_H__
#define __TUTORIAL_BEHAVIOUR_H__

#include <MEngine.h>

class TutorialBehaviour : public MBehavior
{
public:
	TutorialBehaviour(MObject3d * parentObject);
	TutorialBehaviour(TutorialBehaviour & behavior, MObject3d * parentObject);
	~TutorialBehaviour();

	void destroy();
	static MBehavior* getNew(MObject3d* parentObject);
	MBehavior* getCopy(MObject3d* parentObject);

	static const char* getStaticName() { return "Tutorial Controller"; }
	const char* getName() { return getStaticName(); }

	unsigned int getVariablesNumber();
	MVariable getVariable(unsigned int id);

	void update();
	void runEvent(int param){}

private:
	// Exposed values
	float		m_RangeX;
	float		m_StepX;

	// Member variables
	float		m_CurrDeltaX;
	MVector3	m_RootPosition;

	// Private interface
	void Setup(float stepx, float deltax, float rangex);
};

#endif /*__TUTORIAL_BEHAVIOUR_H__*/