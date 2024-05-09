#include "map.h"
#include <stdlib.h>

void	map_init(t_map *map)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		map[i].key = NULL;
		map[i].func = NULL;
	}
}

void	map_insert(t_map *map, char *key, Function func)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (map[i].key == NULL)
		{
			map[i].key = key;
			map[i].func = func;
			return ;
		}
	}
}