/* TutorialGame.cpp
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

#include "TutorialGame.h"

//----------------------------------------
// TutorialGame
//----------------------------------------
TutorialGame::TutorialGame()
:MGame()
{
	// for now, we have nothing to construct
}
//----------------------------------------
TutorialGame::~TutorialGame()
{
	// for now, we have nothing to destruct
}
//----------------------------------------
void TutorialGame::update()
{
	// tick the game clock
	m_Clock.Update();

	MGame::update();
}
//----------------------------------------
GameClock* TutorialGame::GetGameClock()
{
	return &m_Clock;
}
//----------------------------------------
MessageSystem* TutorialGame::GetMessageSystem()
{
	return &m_MessageSystem;
}