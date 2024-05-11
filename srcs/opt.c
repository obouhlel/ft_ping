#include "opt.h"
#include "ping.h"
#include "socket.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

volatile bool g_verbose = false;

bool is_option(const char *str)
{
	return (str[0] == '-' && strlen(str) > 1);
}

static
void opt_help_usage(t_host *host)
{
	(void)host;
	write(1, HELP_USAGE, strlen(HELP_USAGE));
	exit(0);
}

static
void opt_help(t_host *host)
{
	(void)host;
	write(1, HELP, strlen(HELP));
	exit(0);
}

static
void opt_verbose(t_host *host)
{
	host->verbose = true;
}

void map_opt_init(t_map *map, int size)
{
	map_str_insert(map, "-?", &opt_help, size);
	map_str_insert(map, "--help", &opt_help, size);
	map_str_insert(map, "--usage", &opt_help_usage, size);
	map_str_insert(map, "-v", &opt_verbose, size);
	map_str_insert(map, "--verbose", &opt_verbose, size);
}