#ifndef __TUTORIAL_GAME_H__
#define __TUTORIAL_GAME_H__

#include "MEngine.h"

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
	// MGameVirtuals
	//----------------------------------------
	virtual void update();
};

#endif /*__TUTORIAL_GAME_H__*/