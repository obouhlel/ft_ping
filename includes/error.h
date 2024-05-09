#ifndef ERROR_H
#define ERROR_H

#define ERR_MISSING_HOST "ft_ping: missing host operand\nTry 'ping --help' or 'ping --usage' for more information.\n"
#define ERR_UNRECOGNIZED_OPTION "ft_ping: unrecognized option '%s'\nTry 'ping --help' or 'ping --usage' for more information.\n"

int ft_error(const char *msg, char *arg);

#endif