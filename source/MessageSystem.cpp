
// Standard includes
#include "MessageSystem.h"

// Project includes
#include "TutorialGame.h"

// Engine includes
#include <MEngine.h>

// System includes
#include <algorithm> // std::find

MessageSystem::MessageSystem()
: m_CurrID(0)
{
}

Message MessageSystem::RegisterMessage(const char* message)
{
	// For now, we're just going to do something very quick
	// all we want is to have an ID that increases with
	// every message registered
	Message msg = m_CurrID;
	m_CurrID++;
	return msg;

	// in future this should be extended to allow for error
	// checking. This wouldn't be safe, for example, for a
	// multiplayer game, there is no guarantee that messages
	// get registered in the same order. A better solution
	// would be to use a hash of the message name, but then
	// in debug we'd want to do some tests to make sure that
	// we don't have any clashes. For now, this will work.
}

Message RegisterMessage(const char* message)
{
	// This should just wrap up the RegisterMessage function
	// inside the MessageSystem. Making the MessageSystem a
	// singleton would reduce the need for this, but that
	// would not allow us to be able to replace message
	// systems at a later date.
	MEngine* engine = MEngine::getInstance();
	if(MGame* game = engine->getGame())
	{
		TutorialGame* tutGame = (TutorialGame*)game;

		if(MessageSystem* sys = tutGame->GetMessageSystem())
		{
			return sys->RegisterMessage(message);
		}
	}

	// Do we have a sensible fallback behaviour for if we
	// don't have a message system? Nope. Probably best
	// actually doing a simple incremented ID here to be
	// safe.
	return 0;
}

void Subject::AttachObserver(Observer* observer)
{
	// if we're not already being observed by
	// the one being added - then add to the list
	if(std::find(   m_Observers.begin(),
					m_Observers.end(),
					observer) == m_Observers.end())
	{
		m_Observers.push_back(observer);
	}
}
void Subject::DetachObserver(Observer* observer)
{
	// find the correct observer to remove
	observerVecIter iObserver =
		std::find(	m_Observers.begin(),
					m_Observers.end(),
					observer);
	if(iObserver != m_Observers.end())
	{
		m_Observers.erase(iObserver);
	}
}
void Subject::SendMessage(Message message, int param)
{
	// for now, we just send everything to everyone
	// and let them deal with filtering. This isn't
	// an ideal solution, we probably want to extend
	// AttachObserver so we can subscribe to specific
	// messages. 
	observerVecIter iObserver;
	for(iObserver = m_Observers.begin();
		iObserver != m_Observers.end();
		iObserver++)
	{
		(*iObserver)->OnMessage(message, param);
	}
}