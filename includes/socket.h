#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h> // For hostent type
#include <netinet/in.h> // For in_addr and sockaddr_in types
#include <sys/socket.h> // For setsockopt function
#include <sys/time.h> // For timeval type
#include <arpa/inet.h> // For inet_ntoa and inet_addr functions

typedef struct hostent t_hostent;
typedef struct in_addr t_in_addr;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct timeval t_timeval;
typedef struct s_host t_host;
typedef struct iphdr t_ip;

char	*get_ip(char *hostname);
int		setup_socket(t_host *host);

#endif