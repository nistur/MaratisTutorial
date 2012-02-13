/* TutorialGame.h
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

#ifndef __TUTORIAL_GAME_H__
#define __TUTORIAL_GAME_H__

#include "MEngine.h"

#include "GameClock.h"
#include "MessageSystem.h"

DECLARE_MESSAGE(MESSAGE_TEST);

//--------------------------------------------
// TutorialGame
//
// Our friendly neighbourhood game class
// This class should wrap up any game specific
// functionality
//--------------------------------------------
class TutorialGame : public MGame, public Subject
{
public:
	TutorialGame();
	~TutorialGame();
	
	//----------------------------------------
	// MGame virtuals
	//----------------------------------------
	virtual void update();

	//----------------------------------------
	// Public interface
	//----------------------------------------
	GameClock* GetGameClock();
	MessageSystem* GetMessageSystem();

private:
	GameClock m_Clock;

	MessageSystem m_MessageSystem;
};

#endif /*__TUTORIAL_GAME_H__*/