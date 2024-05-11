#include "socket.h"
#include "ping.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*get_ip(char *hostname)
{
	t_hostent	*he = {0};
	t_in_addr	**addr_list = {0};

	he = gethostbyname(hostname);
	if (he == NULL)
		return (NULL);

	addr_list = (t_in_addr **)he->h_addr_list;

	for (int i = 0; addr_list[i] != NULL; i++)
		return (inet_ntoa(*addr_list[i]));
	return (NULL);
}

int setup_socket(t_host *host)
{
	int			sock_fd;
	t_timeval	timeout = {.tv_sec = 1, .tv_usec = 0};

	sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock_fd < 0)
	{
		perror("ping: socket creation failed");
		return (EXIT_FAILURE);
	}
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
	{
		perror("ping: setsockopt failed");
		close(sock_fd);
		return (EXIT_FAILURE);
	}
	host->socket_fd = sock_fd;

	memset(&host->dest_addr, 0, sizeof(host->dest_addr));
	host->dest_addr.sin_family = AF_INET;
	host->dest_addr.sin_port = htons(80);
	host->dest_addr.sin_addr.s_addr = inet_addr(host->ip);

	return (EXIT_SUCCESS);
}