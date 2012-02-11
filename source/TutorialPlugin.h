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