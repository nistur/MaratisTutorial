#include "TutorialBehaviour.h"

#include "TutorialGame.h"

//----------------------------------------
// quick defines
//----------------------------------------
#define BOUNCE_TIMEOUT 5000

//----------------------------------------
// TutorialBehaviour
//----------------------------------------
TutorialBehaviour::TutorialBehaviour(MObject3d * parentObject)
:MBehavior(parentObject)
,m_IsBouncing(false)
{
	Setup(1.0f, 0, 10.0f);
}
//----------------------------------------
TutorialBehaviour::TutorialBehaviour(TutorialBehaviour & behavior, 
							MObject3d * parentObject)
:MBehavior(parentObject)
,m_IsBouncing(false)
{
	Setup(behavior.m_StepX, behavior.m_CurrDeltaX, behavior.m_RangeX);
}
//----------------------------------------
void TutorialBehaviour::Setup(float step, float delta, float range)
{
	// setup the movement information
	m_StepX = step;
	m_CurrDeltaX = delta;
	m_RangeX = range;
	m_StepZ = step;
	m_CurrDeltaZ = delta;
	m_RangeZ = range;

	if(MObject3d* parent = getParentObject())
		m_RootPosition = parent->getPosition();

	MEngine* engine = MEngine::getInstance();
	if(MGame* game = engine->getGame())
	{
		// make a new timer and start it ticking
		TutorialGame* tutGame = (TutorialGame*)game;
		if(GameClock* clock = tutGame->GetGameClock())
		{
			m_BounceTimer = clock->CreateTimer(eBounceTimer);
			m_BounceTimer->AddAction(this);
			m_BounceTimer->SetTimeMs(BOUNCE_TIMEOUT);
			m_BounceTimer->Start();
		}
	}
}
//----------------------------------------
TutorialBehaviour::~TutorialBehaviour(void)
{
	MEngine* engine = MEngine::getInstance();
	if(MGame* game = engine->getGame())
	{
		TutorialGame* tutGame = (TutorialGame*)game;
		if(GameClock* clock = tutGame->GetGameClock())
		{
			clock->DestroyTimer(m_BounceTimer);
		}
	}
}
//----------------------------------------
void TutorialBehaviour::destroy()
{
	delete this;
}
//----------------------------------------
MBehavior* TutorialBehaviour::getNew(MObject3d* parentObject)
{
	return new TutorialBehaviour(parentObject);
}
//----------------------------------------
MBehavior* TutorialBehaviour::getCopy(MObject3d* parentObject)
{
	return new TutorialBehaviour(*this, parentObject);
}
//----------------------------------------
unsigned int TutorialBehaviour::getVariablesNumber()
{
	return 4;
}
//----------------------------------------
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
	case 2:
		return MVariable("ZRange", &m_RangeZ, M_VARIABLE_FLOAT);
		break;
	case 3:
		return MVariable("ZStep", &m_StepZ, M_VARIABLE_FLOAT);
		break;
	default:
		return MVariable("NULL", NULL, M_VARIABLE_NULL);
	}
}
//----------------------------------------
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

	// bouncing
	if(m_IsBouncing)
	{
		m_CurrDeltaZ += m_StepZ;

		// if we hit the top of the bounce
		if( m_CurrDeltaZ >= m_RangeZ )
		{
			// just start going down again
			m_StepZ = -m_StepZ;
		}
		// if we've hit the botoom of the bounce
		else if(m_CurrDeltaZ <= 0)
		{
			// reset the timer and prepare for the next bounce
			m_StepZ = -m_StepZ;
			m_IsBouncing = false;
			m_BounceTimer->SetTimeMs(BOUNCE_TIMEOUT);
			m_BounceTimer->Start();
		}
	}

	MVector3 pos = m_RootPosition;
	pos.x += m_CurrDeltaX;
	pos.z += m_CurrDeltaZ;

	parent->setPosition(pos);
}
//----------------------------------------
void TutorialBehaviour::OnTimerComplete(int id)
{
	// timer has finished, just check which one
	switch(id)
	{
	case eBounceTimer:
		m_IsBouncing = true;
		break;
	};
}