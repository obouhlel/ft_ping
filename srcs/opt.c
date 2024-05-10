#include "opt.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

volatile bool g_verbose = false;

bool is_option(const char *str)
{
	return (str[0] == '-' && strlen(str) > 1);
}

static
void ft_help_usage(void)
{
	write(1, HELP_USAGE, strlen(HELP_USAGE));
	exit(0);
}

static
void ft_help(void)
{
	write(1, HELP, strlen(HELP));
	exit(0);
}

static
void ft_verbose(void)
{
	g_verbose = true;
}

void map_opt_init(t_map_str *map, int size)
{
	map_str_insert(map, "-?", &ft_help, size);
	map_str_insert(map, "--help", &ft_help, size);
	map_str_insert(map, "--usage", &ft_help_usage, size);
	map_str_insert(map, "-v", &ft_verbose, size);
	map_str_insert(map, "--verbose", &ft_verbose, size);
}