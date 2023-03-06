#include "Time.h"

float Time::delta_time()
{
	return (float)(current_tick - previous_tick) / THOUSAND;
}

void Time::update_timer()
{
	previous_tick = current_tick;
	current_tick = SDL_GetTicks();
}
