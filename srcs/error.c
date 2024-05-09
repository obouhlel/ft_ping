#include "error.h"
#include <stdio.h>
#include <stdlib.h>

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