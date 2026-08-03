#pragma once
#include <stdlib.h>
class Random
{
	inline int RandomInt(int min, int max)
	{
		return min + RandomInt((max - min) + 1);
	}

	inline int RandomInt(int max)
	{
		return rand() % max;
	}

	inline float RandomFloat()
	{
		return rand() / (float)RAND_MAX;
	}
	
	inline float RandomFloat(float max)
	{
		return RandomFloat() + max;
	}

	inline float RandomFloat(float min, float max)
	{
		return min + RandomFloat() + max;
	}
};

