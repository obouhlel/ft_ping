#include "map.h"
#include "opt.h"
#include "parsing.h"
#include "socket.h"

int main(int ac, char **av)
{
	t_host	host = {0};

	if (check_args(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	host.hostname = (av[1][0] == '-' && strlen(av[1]) > 1) ? av[2] : av[1];
	if (!is_ip(host.hostname))
		host.ip = get_ip(host.hostname);
	else
		host.ip = host.hostname;
	if (host.ip == NULL)
		return (ft_error(ERR_HOST_UNKNOWN, NULL));
	if (setup_socket(&host) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ping_loop(&host);
	close(host.socket_fd);
	return (EXIT_SUCCESS);
}