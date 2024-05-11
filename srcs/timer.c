#include "timer.h"

void start_timer(t_timer *timer)
{
	clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

void stop_timer(t_timer *timer)
{
	clock_gettime(CLOCK_MONOTONIC, &timer->end);
	timer->time = (timer->end.tv_sec - timer->start.tv_sec) * 1000.0;
	timer->time += (timer->end.tv_nsec - timer->start.tv_nsec) / 1000000.0;
}