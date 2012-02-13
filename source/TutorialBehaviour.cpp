/* TutorialBehaviour.cpp
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

		tutGame->AttachObserver(this);
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
	// we're now using the message from the game
	// to bounce, so don't listen to the timer
	// for now
	/*
	// timer has finished, just check which one
	switch(id)
	{
	case eBounceTimer:
		m_IsBouncing = true;
		break;
	};
	*/
}
//----------------------------------------
void TutorialBehaviour::OnMessage(Message message, int param1)
{
	if(message == MESSAGE_TEST)
	{
		m_IsBouncing = true;
	}
}