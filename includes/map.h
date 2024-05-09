#ifndef MAP_H
#define MAP_H

#include <stdint.h>

typedef struct s_icmp t_icmp;

typedef int (*t_function_ICMP)(t_icmp);
typedef void (*t_function_opt)(void);

typedef struct s_map_int {
	uint8_t			key;
	t_function_ICMP	f;
}	t_map_int;

typedef struct s_map_str
{
	char			*key;
	t_function_opt	f;
}	t_map_str;

void	map_int_insert(t_map_int *map, uint8_t key, t_function_ICMP f, int size);
void	map_str_insert(t_map_str *map, char *key, t_function_opt f, int size);
void	map_type_init(t_map_int *map, int size);
void	map_code_init(t_map_int *map, int size);

#endif