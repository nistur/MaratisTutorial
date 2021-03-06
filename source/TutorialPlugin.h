/* TutorialPlugin.h
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

#ifndef __TUTORIAL_PLUGIN_H__
#define __TUTORIAL_PLUGIN_H__

#ifdef WIN32
#   include <windows.h>
#   define TUTORIAL_EXPORT __declspec(dllexport)
#else
// automagically exported
#   define TUTORIAL_EXPORT
#endif /*WIN32*/

// don't munge the symbol names
#ifdef __cplusplus
extern "C" {
#endif

	TUTORIAL_EXPORT void StartPlugin();
	TUTORIAL_EXPORT void EndPlugin();

#ifdef __cplusplus
}
#endif

#endif /*__TUTORIAL_PLUGIN_H__*/