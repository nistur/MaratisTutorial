#ifndef __TUTORIAL_GAME_H__
#define __TUTORIAL_GAME_H__

#include "MEngine.h"

#include "GameClock.h"

//--------------------------------------------
// TutorialGame
//
// Our friendly neighbourhood game class
// This class should wrap up any game specific
// functionality
//--------------------------------------------
class TutorialGame : public MGame
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

private:
	GameClock m_Clock;
};

#endif /*__TUTORIAL_GAME_H__*/