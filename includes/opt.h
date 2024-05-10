#ifndef OPT_H
#define OPT_H

#include <stdbool.h>
#include <stdlib.h>
#include "map.h"

#define OPT_SIZE 5

#define HELP_USAGE "Usage: ft_ping [-v] HOST...\n"

#define HELP "Usage: ft_ping [OPTION...] HOST ...\nSend ICMP ECHO_REQUEST packets to network hosts.\n\n" \
"Options valid for all request types:\n\n" \
" -v, --verbose\t\t\t\tverbose output\n\n" \
"Options valid for --echo requests:\n\n" \
" -?, --help\t\t\t\tgive this help list\n --usage\t\t\t\tgive a short usage message\n\n"

bool	is_option(const char *str);
void	map_opt_init(t_map_str *map, int size);

#endif