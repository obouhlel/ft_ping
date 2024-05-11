#include "map.h"
#include <stdlib.h>

void	map_str_insert(t_map *map, char *key, t_function_opt f, int size)
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