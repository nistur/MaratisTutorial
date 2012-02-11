#include "TutorialBehaviour.h"

TutorialBehaviour::TutorialBehaviour(MObject3d * parentObject)
:MBehavior(parentObject)
{
	Setup(0, 0, 10.0f);
}

TutorialBehaviour::TutorialBehaviour(TutorialBehaviour & behavior, MObject3d * parentObject)
:MBehavior(parentObject)
{
	Setup(behavior.m_StepX, behavior.m_CurrDeltaX, behavior.m_RangeX);
}

void TutorialBehaviour::Setup(float stepx, float deltax, float rangex)
{
	m_StepX = 0.0f;
	m_CurrDeltaX = 0.0f;
	m_RangeX = 10.0f;

	if(MObject3d* parent = getParentObject())
		m_RootPosition = parent->getPosition();
}

TutorialBehaviour::~TutorialBehaviour(void)
{
}

void TutorialBehaviour::destroy()
{
	delete this;
}

MBehavior* TutorialBehaviour::getNew(MObject3d* parentObject)
{
	return new TutorialBehaviour(parentObject);
}

MBehavior* TutorialBehaviour::getCopy(MObject3d* parentObject)
{
	return new TutorialBehaviour(*this, parentObject);
}

unsigned int TutorialBehaviour::getVariablesNumber()
{
	return 2;
}

MVariable TutorialBehaviour::getVariable(unsigned int id)
{
	switch(id)
	{
	case 0:
		return MVariable("XRange", &m_RangeX, M_VARIABLE_FLOAT);
		break;
	case 1:
		return MVariable("XStep", &m_StepX, M_VARIABLE_FLOAT);
		break;
	default:
		return MVariable("NULL", NULL, M_VARIABLE_NULL);
	}
}

void TutorialBehaviour::update()
{
	MEngine* engine = MEngine::getInstance();

	MGame* game = engine->getGame();

	if(game == 0  || !game->isRunning())
		return;

	MObject3d* parent = getParentObject();

	if(!parent)
		return;

	if(MInputContext* input = engine->getInputContext())
	{
		if(input->isKeyPressed("SPACE"))
		{
			m_CurrDeltaX += m_StepX;

			if( abs(m_CurrDeltaX) >= abs(m_RangeX) )
				m_StepX = -m_StepX;
		}
	}

	MVector3 pos = m_RootPosition;
	pos.x += m_CurrDeltaX;

	parent->setPosition(pos);
}