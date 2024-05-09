#include "map.h"
#include "icmp.h"
#include <stdlib.h>

void	map_int_insert(t_map_int *map, uint8_t key, t_function_ICMP f, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (map[i].key == 255)
		{
			map[i].key = key;
			map[i].f = f;
			return ;
		}
	}
}

void	map_str_insert(t_map_str *map, char *key, t_function_opt f, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (map[i].key == NULL)
		{
			map[i].key = key;
			map[i].f = f;
			return ;
		}
	}
}

void map_type_init(t_map_int *map, int size)
{
	for (int i = 0; i < size; i++)
		map[i].key = 255;
	map_int_insert(map, ICMP_ECHO_REPLY, NULL, size);
	map_int_insert(map, ICMP_ECHO, NULL, size);
	map_int_insert(map, ICMP_TIME_EXCEEDED, NULL, size);
	map_int_insert(map, ICMP_DEST_UNRECHEBLE, NULL, size);
}

void map_code_init(t_map_int *map, int size)
{
	for (int i = 0; i < size; i++)
		map[i].key = 255;
}