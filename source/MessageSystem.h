#ifndef __MESSAGE_SYSTEM_H__
#define __MESSAGE_SYSTEM_H__

typedef unsigned int Message;

//----------------------------------------
// Message System
//
// Currently just a simple wrapper for an
// ID. Can be extended to a more complete
// message system
//----------------------------------------
class MessageSystem
{
public:
	MessageSystem();
	Message RegisterMessage(const char* message);
private:
	Message m_CurrID;
};

// RegisterMessage
// quick accessor for the message system
Message RegisterMessage(const char* message);


// DECLARE_MESSAGE
// this macro should be used in header files to
// expose messages you wish to be sent externally
#define DECLARE_MESSAGE(msg) \
	static extern Message msg;

// REGISTER_MESSAGE
// this macro should go into the source file
#define REGISTER_MESSAGE(msg) \
	Message msg = RegisterMessage(#msg);

//----------------------------------------
// Observer
// 
// Currently just an interface for subject
// to send messages to
// Could be extended to automatically
// remove itself from subjects on destruction
//----------------------------------------
class Observer
{
public:
	virtual void OnMessage(Message message, int param) = 0;
};

#include <vector>

//----------------------------------------
// Subject
// 
// Base class for anything wanting to send
// messages
//----------------------------------------
class Subject
{
public:
	void AttachObserver(Observer* observer);
	void DetachObserver(Observer* observer);

	void SendMessage(Message message, int param);
private:
	typedef std::vector<Observer*>	observerVec;
	typedef observerVec::iterator	observerVecIter;

	observerVec		m_Observers;
};

#endif /*__MESSAGE_SYSTEM_H__*/