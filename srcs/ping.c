#include "ping.h"
#include "timer.h"
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

volatile bool g_running = true;

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
	int len = sizeof(t_icmp);
	unsigned short checksum = packet->checksum;

	packet->checksum = 0;
	if (checksum != calculate_checksum(packet, len))
		return (false);
	return (true);
}

void	signal_handler(int signum)
{
	(void)signum;
	g_running = false;
}

void update_stats(t_ping_stats *stats, t_timer *timer)
{
	stats->sum_time += timer->time;
	stats->sum_time_squared += timer->time * timer->time;
	if (timer->time < stats->min_time || stats->min_time == 0)
		stats->min_time = timer->time;
	if (timer->time > stats->max_time)
		stats->max_time = timer->time;
}

void print_stats(t_host *host, t_ping_stats *stats)
{
    double	avg = stats->sum_time / stats->received;
    double	variance = (stats->sum_time_squared / stats->received) - (avg * avg);
    double	stddev = sqrt(variance);

    printf("--- %s ping statistics ---\n", host->hostname);
    printf("%d packets transmitted, %d received, %d%% packet loss\n", stats->transmitted, stats->received, ((stats->transmitted - stats->received) * 100) / stats->transmitted);
    printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", stats->min_time, avg, stats->max_time, stddev);
}

int send_ping(t_host *host, t_ping_stats *stats, t_timer *timer)
{
	ssize_t			ret = 0;
	char			buffer[BUFFER_SIZE] = {0};
	t_icmp			*icmp = (t_icmp *)buffer;
	static int		seq = 0;

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->checksum = 0; 
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = seq++;

	icmp->checksum = calculate_checksum(icmp, sizeof(t_icmp));

	start_timer(timer);
	ret = sendto(host->socket_fd, buffer, BUFFER_SIZE, 0, (t_sockaddr *)&(host->dest_addr), sizeof(host->dest_addr));
	if (ret < 0)
	{
		perror("ping: sendto failed");
		return (EXIT_FAILURE);
	}
	stats->transmitted++;
	return (EXIT_SUCCESS);
}

int recv_ping(t_host *host, t_ping_stats *stats, t_timer *timer)
{
	ssize_t		ret = 0;
	char		buffer[BUFFER_SIZE] = {0};
	socklen_t	len = sizeof(host->dest_addr);
	t_icmp		*icmp = NULL;
	t_ip		*ip = NULL;
	static int	old_seq = -1;

	ret = recvfrom(host->socket_fd, buffer, BUFFER_SIZE, 0, (t_sockaddr *)&(host->dest_addr), &len);
	if (ret < 0)
	{
		perror("ping: recvfrom failed");
		return (EXIT_FAILURE);
	}
	ip = (t_ip *)buffer;
	icmp = (t_icmp *)(buffer + sizeof(t_ip));
	if (!checksum_icmp(icmp))
		return (EXIT_SUCCESS);
	if (icmp->type != ICMP_ECHOREPLY && !host->verbose)
		return (EXIT_SUCCESS);
	if (icmp->un.echo.sequence == old_seq)
	{
		stats->transmitted--;
		stats->to_update = false;
		return (EXIT_SUCCESS);
	}
	stop_timer(timer);
	printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", ret, host->ip, icmp->un.echo.sequence, ip->ttl, timer->time);
	stats->received++;
	old_seq = icmp->un.echo.sequence;
	return (EXIT_SUCCESS);
}

void	ping_loop(t_host *host)
{
	t_ping_stats	stats = {0};
	t_timer			timer;
	int				id = getpid();

	printf("PING %s (%s): %ld data bytes", host->hostname, host->ip, BUFFER_SIZE - sizeof(t_icmp));
	if (host->verbose)
		printf(", id 0x%x = %d\n", id, id);
	else
		printf("\n");
	signal(SIGINT, &signal_handler);
	while (g_running)
	{
		bzero(&timer, sizeof(t_timer));
		stats.to_update = true;
		send_ping(host, &stats, &timer);
		recv_ping(host, &stats, &timer);
		if (stats.to_update)
			update_stats(&stats, &timer);
		if (strcmp(host->ip, "127.0.0.1") == 0)
			usleep(500000);
		else
			sleep(1);
	}
	print_stats(host, &stats);
}