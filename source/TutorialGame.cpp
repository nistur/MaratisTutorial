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