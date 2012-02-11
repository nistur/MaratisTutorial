// Standard include
#include "TutorialPlugin.h"

// Project includes
#include "TutorialBehaviour.h"
#include "TutorialGame.h"

// System includes

// static games.
MGame* s_prevGame = NULL;
TutorialGame* s_tutGame = NULL;

void StartPlugin()
{
	MEngine* engine = MEngine::getInstance();
	MBehaviorManager * behaviorManager = engine->getBehaviorManager();
	behaviorManager->addBehavior(TutorialBehaviour::getStaticName(), 
								M_OBJECT3D, 
								TutorialBehaviour::getNew);

	// just cache the previous game, shouldn't need to, but just in case
	s_prevGame = engine->getGame();
	s_tutGame = new TutorialGame;
	engine->setGame(s_tutGame);
}

void EndPlugin()
{
	// check that the game we're removing is ourself
	MEngine* engine = MEngine::getInstance();
	if(engine->getGame() == s_tutGame)
		engine->setGame(s_prevGame);
	// delete me
	SAFE_DELETE(s_tutGame);
}