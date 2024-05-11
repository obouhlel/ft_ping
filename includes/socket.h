#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/time.h>

#include <netdb.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

typedef struct hostent t_hostent;
typedef struct in_addr t_in_addr;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct timeval t_timeval;
typedef struct icmphdr t_icmp;
typedef struct iphdr t_ip;

#define BUFFER_SIZE 64
 
typedef struct s_ping_stats {
	int		transmitted;
	int		received;
	long	min_time;
	long	max_time;
	long	sum_time;
	long	sum_time_squared;
}	t_ping_stats;

typedef struct s_host {
	char		*hostname;
	char		*ip;
	int			socket_fd;
}	t_host;

char	*get_ip(char *hostname);
int		setup_socket(t_host *host);
void	ping_loop(t_host *host);

#endif