#ifndef SOCKET_H
#define SOCKET_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

typedef struct hostent t_hostent;
typedef struct in_addr t_in_addr;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct timeval t_timeval;
typedef struct icmphdr t_icmphdr;
typedef struct iphdr t_ip;

#define BUFFER_SIZE 1024
#define ICMP_ECHO_REPLY 0
#define ICMP_ECHOREQ 8
#define ICMP_DATA_SIZE 56

typedef struct s_icmp {
    t_icmphdr hdr;
    char data[ICMP_DATA_SIZE];
} t_icmp;

typedef struct s_ping_stats {
    int transmitted;
    int received;
    long min_time;
    long max_time;
    long sum_time;
    long sum_time_squared;
} t_ping_stats;

typedef struct s_host {
	char		*hostname;
	char		*ip;
	t_sockaddr	addr;
	int			socket_fd;
}	t_host;

char	*get_ip(char *hostname);
int		setup_socket(t_host *host);
void	ping_loop(t_host *host);

#endif