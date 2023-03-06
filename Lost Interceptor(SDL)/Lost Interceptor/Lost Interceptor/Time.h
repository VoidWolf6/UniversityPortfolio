#pragma once
#include <SDL.h>

class Time
{
public:
	float delta_time();
	void update_timer();

private:
	unsigned int previous_tick;
	unsigned int current_tick;
	const int THOUSAND = 1000;
};

