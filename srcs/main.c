#include "icmp.h"
#include <stdio.h>
#include <stdlib.h>

int check_args(int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s <hostname>\n", av[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	if (check_args(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}