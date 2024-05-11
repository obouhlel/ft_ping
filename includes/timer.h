#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct timespec t_timespec;

typedef struct s_timer {
	t_timespec	start;
	t_timespec	end;
	double		time;
}	t_timer;

void start_timer(t_timer *timer);
void stop_timer(t_timer *timer);

#endif