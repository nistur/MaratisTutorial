/* InputManager.h
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

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

//----------------------------------------
// InputCommand
//
// Interface for input commands, will send
// a OnKeyPressed and OnKeyReleased signal
//----------------------------------------
class InputCommand
{
public:
	InputCommand();

	virtual const char* GetCommandName() = 0;
	virtual void		OnKeyPressed() {}
	virtual void		OnKeyReleased() {}

	const char*			GetKeyName() { return m_KeyName; }
	void				SetKeyName(const char* keyName);

private:
	const char* m_KeyName;
};

#include <vector>

//----------------------------------------
// InputManager
//
// Simple input manager wrapper to send
// commands when a key is pressed.
// This provides a nice, central place for
// when we might want to write modifiable
// keys
//----------------------------------------
class InputManager
{
public:
	InputManager();
	~InputManager();

	// Command interface
	void RegisterCommand(InputCommand* command);
	void UnregisterCommand(InputCommand* command);

	void Update();
private:
	//------------------------------------
	// commandDef
	//
	// Tiny little struct just to hold the
	// callback command, and the current
	// state of that key
	//------------------------------------
	struct commandDef
	{
		enum commandState
		{
			eUp,
			ePressed,
			eDown,
			eReleased,
		};

		InputCommand*	command;
		commandState	state;
	};

	typedef std::vector<commandDef*>	commandVec;
	typedef commandVec::iterator		commandVecIter;

	commandVec	m_Commands;
};

#endif /*__INPUT_MANAGER_H__*/
