#include "socket.h"

unsigned short calculate_checksum(void *b, int len)
{
	unsigned short	*buf = b;
	unsigned int	sum = 0;
	unsigned short	result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;

	if (len == 1)
		sum += *(unsigned char*)buf;

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

bool	checksum_icmp(t_icmp *icmp_packet)
{
	t_icmp *packet = icmp_packet;
	int len = sizeof(icmp_packet);
	unsigned short checksum = packet->checksum;

	packet->checksum = 0;
	if (checksum != calculate_checksum(packet, len))
		return (false);
	return (true);
}

t_icmp *create_icmp_packet_send(char buffer[BUFFER_SIZE])
{
	t_icmp *icmp = (t_icmp *)buffer;

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->checksum = 0; 
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = 0;

	icmp->checksum = calculate_checksum(icmp, sizeof(t_icmp));
	return (icmp);
}

t_icmp *create_icmp_packet_recv(char *buffer)
{
	t_icmp *icmp = (t_icmp *)buffer;

	return (icmp);
}

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
	int sock_fd;
	t_timeval timeout = {.tv_sec = 1, .tv_usec = 0};

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
	return (EXIT_SUCCESS);
}

void	print_icmp(t_icmp *icmp)
{
	printf("ICMP packet:\n");
	printf("type: %d\n", icmp->type);
	printf("code: %d\n", icmp->code);
	printf("checksum: %d\n", icmp->checksum);
	printf("id: %d\n", icmp->un.echo.id);
	printf("sequence: %d\n", icmp->un.echo.sequence);
}

int send_ping(t_host *host)
{
	ssize_t			ret = 0;
	char			buffer[BUFFER_SIZE] = {0};
	t_icmp			*icmp = create_icmp_packet_send(buffer);
	t_sockaddr_in	addr = {0};
	int				addr_len = sizeof(addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr(host->ip);

	ret = sendto(host->socket_fd, buffer, BUFFER_SIZE, 0, (t_sockaddr *)&addr, addr_len);
	if (ret < 0)
	{
		perror("ping: sendto failed");
		return (EXIT_FAILURE);
	}
	printf("------ Sent ICMP packet ------\n");
	print_icmp(icmp);
	printf("-------------------------------\n");
	return (EXIT_SUCCESS);
}

int recv_ping(t_host *host)
{
	ssize_t ret = 0;
	char buffer[BUFFER_SIZE + sizeof(t_ip)] = {0};
	t_sockaddr_in addr = {0};
	socklen_t len = sizeof(addr);
	t_icmp *icmp = NULL;

	t_ip *ip = (t_ip *)buffer;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr(host->ip);

	ret = recvfrom(host->socket_fd, buffer, BUFFER_SIZE, 0, (t_sockaddr *)&addr, &len);
	if (ret < 0)
	{
		perror("ping: recvfrom failed");
		return (EXIT_FAILURE);
	}

	printf("------ Received ICMP packet ------\n");
	icmp = create_icmp_packet_recv(buffer + sizeof(t_ip));
	printf("Checksum: %s\n", checksum_icmp(icmp) ? "OK" : "KO");
	printf("TTL: %d\n", ip->ttl);
	print_icmp(icmp);
	printf("----------------------------------\n");
	return (EXIT_SUCCESS);
}

void	ping_loop(t_host *host)
{
	printf("PING %s (%s)\n", host->hostname, host->ip);
	if (send_ping(host) == EXIT_FAILURE)
		return ;
	if (recv_ping(host) == EXIT_FAILURE)
		return ;
}