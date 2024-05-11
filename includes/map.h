#ifndef MAP_H
#define MAP_H

#include <stdint.h>

typedef struct s_host t_host;

typedef void (*t_function_opt)(t_host *host);

typedef struct s_map
{
	char			*key;
	t_function_opt	f;
}	t_map;

void	map_str_insert(t_map *map, char *key, t_function_opt f, int size);

#endif