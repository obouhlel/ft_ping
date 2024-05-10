#ifndef MAP_H
#define MAP_H

#include <stdint.h>

typedef void (*t_function_opt)(void);

typedef struct s_map_str
{
	char			*key;
	t_function_opt	f;
}	t_map_str;

void	map_str_insert(t_map_str *map, char *key, t_function_opt f, int size);

#endif