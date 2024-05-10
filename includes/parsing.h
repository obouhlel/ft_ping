#ifndef PARSING_H
#define PARSING_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERR_MISSING_HOST "ft_ping: missing host operand\nTry 'ping --help' or 'ping --usage' for more information.\n"
#define ERR_UNRECOGNIZED_OPTION "ft_ping: unrecognized option '%s'\nTry 'ping --help' or 'ping --usage' for more information.\n"
#define ERR_HOST_UNKNOWN "ft_ping: unkwon host\n"

int		ft_error(const char *msg, char *arg);
int		check_args(int ac, char **av);
bool	is_ip(char *host);

#endif