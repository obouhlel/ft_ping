#include "icmp.h"
#include "map.h"
#include "opt.h"
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	const char	*host;
	t_map_int map_type[SIZE_TYPE_ICMP] = {0};
	// t_map_int map_code[SIZE_CODE_ICMP] = {0};
	// t_icmp icmp = {0};

	map_type_init(map_type, SIZE_TYPE_ICMP);
	// map_code_init(map_code, SIZE_CODE_ICMP);
	if (check_args(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	host = (av[1][0] == '-' && strlen(av[1]) > 1) ? av[2] : av[1];
	printf("host = %s\n", host);
	return (EXIT_SUCCESS);
}