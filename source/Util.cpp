#include "Util.h"
#include <string>

unsigned int Util::Hash(const char* str)
{
	unsigned int len = strlen(str);
	unsigned int hash = 0;
	unsigned int i    = 0;
	for(i = 0; i < len; str++, i++)
	{
		hash = hash << 7 ^ (*str);
	}

	return hash;
}