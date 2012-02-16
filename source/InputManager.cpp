/* InputManager.cpp
  version 0.0.1, February 15th, 2012

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

#include "InputManager.h"

#include <MEngine.h>

//----------------------------------------
InputCommand::InputCommand()
: m_KeyName(0)
{
}
//----------------------------------------
void InputCommand::SetKeyName(const char* keyName)
{
	m_KeyName = keyName;
}
//----------------------------------------
InputManager::InputManager()
{
	// for now, we don't really
	// care much for constructing
	// anything
}
//----------------------------------------
InputManager::~InputManager()
{
	// just make sure our command list is properly
	// empty. We don't care about the commands
	// themselves, because we don't own them
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		delete *iCommand;
	}
	m_Commands.clear();
}
//----------------------------------------
void InputManager::RegisterCommand(InputCommand* command)
{
	// first thing's first. We don't want to
	// be adding duplicate commands
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		// this command is already registered
		if((*iCommand)->command == command)
			return;
	}
	// all is a-ok
	// create a new command and set it up
	commandDef* newCommand = new commandDef;
	newCommand->command = command;
	newCommand->state = commandDef::eUp;
	m_Commands.push_back(newCommand);
}
//----------------------------------------
void InputManager::UnregisterCommand(InputCommand* command)
{
	// unfortunately we can't do an std::find here
	// as we aren't adding the command to the vector
	// itself
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		if((*iCommand)->command == command)
		{
			delete *iCommand;
			m_Commands.erase(iCommand);
			// we should never have duplicate commands
			// so there's no reason why we can't just
			// drop out here
			return;
		}
	}
}
//----------------------------------------
void InputManager::Update()
{
	MEngine* engine = MEngine::getInstance();
	
	if(MInputContext* input = engine->getInputContext())
	{
		// this bit is simple, just loop through the
		// commands we have registered
		for(commandVecIter iCommand = m_Commands.begin(); 
			iCommand != m_Commands.end(); 
			iCommand++)
		{
			commandDef::commandState state = (*iCommand)->state;
			// find out what state the key is which is bound to 
			// this command
			if(input->isKeyPressed((*iCommand)->command->GetKeyName()))
			{
				// if it's down, check the previous state
				switch(state)
				{
				case commandDef::eUp:
				case commandDef::eReleased:
					// we only just pressed it, so send the key pressed
					// command
					(*iCommand)->command->OnKeyPressed();
					(*iCommand)->state = commandDef::ePressed;
					break;
				case commandDef::ePressed:
				case commandDef::eDown:
					// it was already down, just make sure it's now
					// saved as down
					(*iCommand)->state = commandDef::eDown;
					break;
				}
			}
			else
			{
				// same deal for up, but in reverse
				switch(state)
				{
				case commandDef::eUp:
				case commandDef::eReleased:
					(*iCommand)->state = commandDef::eUp;
					break;
				case commandDef::ePressed:
				case commandDef::eDown:
					(*iCommand)->command->OnKeyReleased();
					(*iCommand)->state = commandDef::eReleased;
					break;
				}
			}
		}
	}
}