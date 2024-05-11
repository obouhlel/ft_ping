#include "parsing.h"
#include "opt.h"
#include "error.h"
#include "socket.h"

int ft_error(const char *msg, char *arg)
{
	if (arg)
	{
		fprintf(stderr, msg, arg);
	}
	else
	{
		fprintf(stderr, msg);
	}
	return (EXIT_FAILURE);
}

int	check_args(int ac, char **av, t_host *host)
{
	t_map	opt[OPT_SIZE] = {0};
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
				opt[i].f(host);
				break ;
			}
		}
		if (i == OPT_SIZE)
			return (ft_error(ERR_UNRECOGNIZED_OPTION, av[1]));
	}
	if (have_option && av[2] == NULL)
		return (ft_error(ERR_MISSING_HOST, NULL));
	return (EXIT_SUCCESS);
}

bool is_ip(char *host)
{
	int i = 0;
	int n = 0;
	int nb_digit = 0;

	for (int j = 0; j < 4; j++)
	{
		n = 0;
		while (host[i] && isdigit(host[i]))
		{
			i++;
			n++;
		}
		if (n > 3 || (j < 3 && !host[i]))
			return false;
		if (j < 3 && host[i] == '.')
		{
			nb_digit++;
			i++;
		}
	}
	return (nb_digit == 3 && host[i] == '\0');
}