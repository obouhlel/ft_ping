#ifndef PING_H
#define PING_H

#define BUFFER_SIZE 64

#include <stdlib.h>
#include <stdbool.h> // For bool type
#include <netinet/ip_icmp.h> // For icmphdr type
#include <netinet/ip.h> // For iphdr type
#include <netinet/in.h> // For sockaddr_in type

typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct iphdr t_ip;
typedef struct icmphdr t_icmp;

typedef struct s_ping_stats {
	bool	to_update;
	int		transmitted;
	int		received;
	double	min_time;
	double	max_time;
	double	sum_time;
	double	sum_time_squared;
}	t_ping_stats;

typedef struct s_host {
	char			*hostname;
	char			*ip;
	int				socket_fd;
	t_sockaddr_in	dest_addr;
	bool			verbose;
}	t_host;

void	ping_loop(t_host *host);

#endif