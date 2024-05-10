#include "socket.h"

void update_ping_stats(t_ping_stats *stats, long time)
{
	stats->transmitted++;
	stats->received++;
	if (time < stats->min_time || stats->min_time == 0)
		stats->min_time = time;
	if (time > stats->max_time)
		stats->max_time = time;
	stats->sum_time += time;
	stats->sum_time_squared += time * time;
}

void print_ping_stats(t_ping_stats *stats, char *hostname)
{
	long avg_time = stats->sum_time / stats->received;
	long variance = (stats->sum_time_squared / stats->received) - (avg_time * avg_time);
	long stddev_time = sqrt(variance);

	printf("--- %s ping statistics ---\n", hostname);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", stats->transmitted, stats->received, (stats->transmitted - stats->received) * 100 / stats->transmitted);
	printf("round-trip min/avg/max/stddev = %ld/%ld/%ld/%ld ms\n", stats->min_time, avg_time, stats->max_time, stddev_time);
}

unsigned short calculate_checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;

	if (len == 1)
		sum += *(unsigned char*)buf;

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

bool	checksum_icmp(t_icmp icmp_packet)
{
	t_icmp *packet = &icmp_packet;
	int len = sizeof(icmp_packet);
	unsigned short checksum = packet->hdr.checksum;

	packet->hdr.checksum = 0;
	if (checksum != calculate_checksum(packet, len))
		return (false);
	return (true);
}

t_icmp create_icmp_packet(void)
{
	t_icmp	icmp_packet = {0};

	icmp_packet.hdr.type = ICMP_ECHO;
	icmp_packet.hdr.code = 0;
	icmp_packet.hdr.checksum = 0;
	icmp_packet.hdr.un.echo.id = 0;
	icmp_packet.hdr.un.echo.sequence = 0;

	for (int i = 0; i < ICMP_DATA_SIZE; i++)
		icmp_packet.data[i] = i;

	icmp_packet.hdr.checksum = calculate_checksum(&icmp_packet, sizeof(t_icmp));

	return (icmp_packet);
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

int send_ping(t_host *host)
{
	ssize_t	ret = 0;
	t_icmp	icmp = create_icmp_packet();

	ret = sendto(host->socket_fd, &icmp, sizeof(t_icmp), 0, (t_sockaddr *)&host->addr, sizeof(host->addr));
	if (ret < 0)
	{
		perror("ping: sendto failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int revc_ping(t_host *host)
{
	ssize_t		ret = 0;
	t_icmp		icmp = {0};
	socklen_t	len = sizeof(host->addr);

	ret = recvfrom(host->socket_fd, &icmp, sizeof(t_icmp), 0, (t_sockaddr *)&host->addr, &len);
	if (ret < 0)
	{
		perror("ping: recvfrom failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ping_loop(t_host *host)
{
	bool	ping = true;
	t_ping_stats stats = {0};

	printf("PING %s (%s): %d data bytes\n", host->hostname, host->ip, ICMP_DATA_SIZE);
	while (ping)
	{
		struct timeval start, end;
		long mtime, seconds, useconds;

		gettimeofday(&start, 0);
		if (send_ping(host) == EXIT_FAILURE)
			return ;
		stats.transmitted++;
		if (revc_ping(host) == EXIT_FAILURE)
			return ;
		gettimeofday(&end, 0);
		seconds  = end.tv_sec  - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;
		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		update_ping_stats(&stats, mtime);
		sleep(1);
	}
	print_ping_stats(&stats, host->hostname);
}