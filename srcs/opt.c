#include "opt.h"
#include "error.h"
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

int	check_args(int ac, char **av)
{
	t_map_str	opt[OPT_SIZE] = {0};
	bool		have_option = false;
	int			i = 0;

	map_opt_init(opt, OPT_SIZE);
	if (ac < 2)
		return (ft_error(ERR_MISSING_HOST, NULL));
	if (is_option(av[1]))
	{
		have_option = true;
		for (i = 0; i < OPT_SIZE; i++)
		{
			if (strcmp(av[1], opt[i].key) == 0)
			{
				opt[i].f();
				break ;
			}
		}
		if (i == OPT_SIZE)
			return (ft_error(ERR_UNRECOGNIZED_OPTION, av[1]));
	}
	if (have_option && av[2] == NULL)
		return (ft_error(ERR_MISSING_HOST, NULL));
	// printf("\nDEBUG: g_verbose = %s\n", g_verbose ? "true" : "false");
	return (EXIT_SUCCESS);
}